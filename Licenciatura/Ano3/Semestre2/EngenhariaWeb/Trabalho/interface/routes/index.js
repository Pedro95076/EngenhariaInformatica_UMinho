var express = require('express');
var router = express.Router();
var axios = require('axios');
var passport = require('passport')
var auth = require('../auth/auth');
var multer = require('multer');
var FormData = require('form-data');
const NodeCache = require('node-cache');
var jwt = require('jsonwebtoken');
var fs = require('fs')
var path = require('path')

// Create a cache that stores items for 1 day
const imageCache = new NodeCache({ stdTTL: 86400 });

const cacheMiddleware = async (req, res, next) => {
    const filename = req.params.filename;
    const imagename = req.params.imagename;
    const cacheKey = `${filename}-${imagename}`;
    const cachedImage = imageCache.get(cacheKey);

    if (cachedImage) {
        console.log('Serving image from cache:', cacheKey);
        res.writeHead(200, { 'Content-Type': 'image/jpeg' });
        res.end(cachedImage, 'binary');
    } else {
        const imageURL = `http://api:3000/ruas/images/${filename}/${decodeURIComponent(imagename)}`;
        console.log(`Fetching image from URL: ${imageURL}`);

        try {
            const response = await axios.get(imageURL, { responseType: 'arraybuffer' });
            const imageBuffer = response.data;

            imageCache.set(cacheKey, imageBuffer);

            console.log('Serving image from remote and caching:', cacheKey);
            res.writeHead(200, { 'Content-Type': 'image/jpeg' });
            res.end(imageBuffer, 'binary');
        } catch (err) {
            console.error(`Error fetching image: ${err.message}`);
            res.status(404).send('Imagem não encontrada.');
        }
    }
};

var storage = multer.diskStorage({
  destination: function (req, file, cb) {
      cb(null, 'uploads/');
  },
  filename: function (req, file, cb) {
      cb(null, Date.now() + path.extname(file.originalname));
  }
});

var upload = multer({ storage: storage });

/* GET home page */
router.get('/', function(req, res, next) {
  var date = new Date().toISOString().substring(0,16);
  res.status(200).render('home', { d: date });
});

/* GET list of roads page */
router.get('/ruas', function(req, res, next){
  var date = new Date().toISOString().substring(0,16);
  axios.get('http://api:3000/ruas')
    .then( response => {
      res.status(200).render('ruas', {ruas: response.data, d: date})
    })
    .catch(erro => {
      res.render('error', {message: 'Não foi possível obter a página com a lista de ruas.', error: erro})
    })
});

/* GET list of roads by name, date, entity or place */
router.get('/ruas/pesquisa', function(req, res, next){
  var date = new Date().toISOString().substring(0,16);
  if(req.query.ordem){
    axios.get('http://api:3000/ruas?ordem=' + req.query.ordem)
      .then( response => {
        res.status(200).render('ruas', {ruas: response.data, d: date})
      })
      .catch(erro => {
        res.render('error', {message: 'Não foi possível obter a lista de ruas por pesquisa.', error: erro})
      })
  } else {
    axios.get('http://api:3000/ruas?elemento=' + req.query.elemento)
      .then( response => {
        res.status(200).render('ruas', {ruas: response.data, d: date})
      })
    .catch(erro => {
      res.render('error', {message: 'Não foi possível obter a lista de ruas por elemento.', error: erro})
    })
  }
});

/* GET form for addRua */
router.get('/ruas/add', auth.verificaAcesso('admin'), function(req, res, next) {
  var date = new Date().toISOString().substring(0,16);
  res.status(200).render('addRua', {d:date})
});

/* POST rua */
router.post('/ruas/add', auth.verificaAcesso('admin'), upload.array('imagens', 12), async function (req, res, next) {
  try {
      const formData = new FormData();

      // Append non-file fields to FormData
      Object.entries(req.body).forEach(([key, value]) => {
          if (key !== 'lista_casas' && key !== 'imagens' && key !== 'entidades' && key !== 'datas' && key !== 'lugares' && key !== 'figuraId' && key !== 'legenda' && key !== 'id') {
              if (Array.isArray(value)) {
                  value.forEach(item => formData.append(`${key}[]`, item));
              } else {
                  formData.append(key, value);
              }
          }
      });

      // Handle lista_casas separately
      const lista_casas = req.body.lista_casas ? (Array.isArray(req.body.lista_casas) ? req.body.lista_casas : [req.body.lista_casas]) : [];
      lista_casas.forEach((casa, index) => {
          Object.entries(casa).forEach(([key, value]) => {
              formData.append(`lista_casas[${index}][${key}]`, value);
          });
      });

      // Handle entidades separately
      const entidades = req.body.entidades ? (Array.isArray(req.body.entidades) ? req.body.entidades : [req.body.entidades]) : [];
      entidades.forEach((entidade, index) => {
          Object.entries(entidade).forEach(([key, value]) => {
              formData.append(`entidades[${index}][${key}]`, value);
          });
      });

      // Handle datas separately
      const datas = req.body.datas ? (Array.isArray(req.body.datas) ? req.body.datas : [req.body.datas]) : [];
      datas.forEach((data, index) => {
          Object.entries(data).forEach(([key, value]) => {
              formData.append(`datas[${index}][${key}]`, value);
          });
      });

      // Handle lugares separately
      const lugares = req.body.lugares ? (Array.isArray(req.body.lugares) ? req.body.lugares : [req.body.lugares]) : [];
      lugares.forEach((lugar, index) => {
          Object.entries(lugar).forEach(([key, value]) => {
              formData.append(`lugares[${index}][${key}]`, value);
          });
      });

      const figuraIds = req.body.figuraId ? (Array.isArray(req.body.figuraId) ? req.body.figuraId : [req.body.figuraId]) : [];
      const legendas = req.body.legenda ? (Array.isArray(req.body.legenda) ? req.body.legenda : [req.body.legenda]) : [];
      const ids = req.body.id ? (Array.isArray(req.body.id) ? req.body.id : [req.body.id]) : [];

      figuraIds.forEach((figuraId, index) => {
          formData.append(`figuraId[]`, figuraId);
          formData.append(`legenda[]`, legendas[index]);
          formData.append(`id[]`, ids[index]);
      });

      console.log('aqui');

      // Append files to FormData
      req.files.forEach(file => {
          console.log('File path:', file.path);
          formData.append('imagens', fs.createReadStream(file.path), { filename: file.originalname });
      });

      console.log('FormData: ', formData);

      const response = await axios.post('http://api:3000/ruas/add', formData, {
          headers: formData.getHeaders(),
      });

      res.status(200).redirect('/ruas/' + response.data._id);
  } catch (erro) {
      res.status(603).render('error', { error: erro });
  }
});

/* GET edit page */
router.get('/ruas/edit/:idRua', auth.verificaAcesso('admin'), function(req, res, next){
  var date = new Date().toISOString().substring(0,16);

  const roadURL = 'http://api:3000/ruas/' + req.params.idRua;

  axios.get(roadURL)
    .then(response => {
      const rua = response.data;
      res.status(200).render('editRua', {
        rua,
        d: date
      });
    })
    .catch(erro => {
      res.status(500).render('error', {
        message: erro.message,
        error: erro
      });
    });
});

/* POST edit page */
router.post('/ruas/edit/:idRua', auth.verificaAcesso('admin'), upload.array('imagens'), async function(req, res, next) {
  try {
    const formData = new FormData();

    console.log('aqui')

    // Append non-file fields to FormData
    Object.entries(req.body).forEach(([key, value]) => {
        if (key !== 'lista_casas' && key !== 'imagens' && key !== 'entidades' && key !== 'datas' && key !== 'lugares' && key !== 'figuraId' && key !== 'legenda' && key !== 'id') {
            if (Array.isArray(value)) {
                value.forEach(item => formData.append(`${key}[]`, item));
            } else {
                formData.append(key, value);
            }
        }
    });

    console.log('aqui')

    // Handle lista_casas separately
    const lista_casas = req.body.lista_casas ? (Array.isArray(req.body.lista_casas) ? req.body.lista_casas : [req.body.lista_casas]) : [];
    lista_casas.forEach((casa, index) => {
        Object.entries(casa).forEach(([key, value]) => {
            formData.append(`lista_casas[${index}][${key}]`, value);
        });
    });

    console.log('aqui')

    // Handle entidades separately
    const entidades = req.body.entidades ? (Array.isArray(req.body.entidades) ? req.body.entidades : [req.body.entidades]) : [];
    entidades.forEach((entidade, index) => {
        Object.entries(entidade).forEach(([key, value]) => {
            formData.append(`entidades[${index}][${key}]`, value);
        });
    });

    console.log('aqui')

    // Handle datas separately
    const datas = req.body.datas ? (Array.isArray(req.body.datas) ? req.body.datas : [req.body.datas]) : [];
    datas.forEach((data, index) => {
        Object.entries(data).forEach(([key, value]) => {
            formData.append(`datas[${index}][${key}]`, value);
        });
    });

    // Handle lugares separately
    const lugares = req.body.lugares ? (Array.isArray(req.body.lugares) ? req.body.lugares : [req.body.lugares]) : [];
    lugares.forEach((lugar, index) => {
        Object.entries(lugar).forEach(([key, value]) => {
            formData.append(`lugares[${index}][${key}]`, value);
        });
    });

    // Append files to FormData
    req.files.forEach(file => {
        console.log('aqui')
        console.log(file.path)
        formData.append('imagens', fs.createReadStream(file.path), { filename: file.originalname });
    });

    // Append figuraId, legenda, id arrays
    const figuraIds = req.body.figuraId ? (Array.isArray(req.body.figuraId) ? req.body.figuraId : [req.body.figuraId]) : [];
    const legendas = req.body.legenda ? (Array.isArray(req.body.legenda) ? req.body.legenda : [req.body.legenda]) : [];
    const ids = req.body.id ? (Array.isArray(req.body.id) ? req.body.id : [req.body.id]) : [];

    figuraIds.forEach((figuraId, index) => {
        formData.append(`figuraId[]`, figuraId);
        formData.append(`legenda[]`, legendas[index]);
        formData.append(`id[]`, ids[index]);
    });

    // Realiza a requisição POST usando axios
    const response = await axios.put(`http://api:3000/ruas/edit/${req.params.idRua}`, formData, {
        headers: formData.getHeaders(),
    });

    res.status(200).redirect(`/ruas/${response.data._id}`);
  } catch (erro) {
    console.error('Erro ao enviar requisição:', erro);
    res.status(603).render('error', { error: erro });
  }
});


router.get('/posts', auth.verificaAcesso(['user', 'admin']), function(req, res, next) {
  var date = new Date().toISOString().substring(0, 16);

  // Extract the token from the request headers
  const token = req.cookies.token;
  console.log('Received token:', token);

  // Fetch posts and ruas concurrently
  const fetchPosts = axios.get('http://api:3000/posts/', {
    headers: {
      Authorization: token
    }
  });
  const fetchRuas = axios.get('http://api:3000/ruas/', {
    headers: {
      Authorization: token
    }
  });

  Promise.all([fetchPosts, fetchRuas])
    .then(responses => {
      const posts = responses[0].data;
      const ruas = responses[1].data;

      const userPromises = [];
      const ruaPromises = [];
      const commentPromises = [];
      const usersMap = {};
      const ruasMap = {};
      const commentsMap = {};

      posts.forEach(post => {
        if (!post) {
          console.warn('Null or undefined post found:', post);
          return;
        }

        // Fetch users if not already fetched
        if (post.user_id && !usersMap[post.user_id]) {
          userPromises.push(
            axios.get('http://api:3000/users/' + post.user_id, {
              headers: {
                Authorization: token
              }
            })
              .then(response => {
                usersMap[post.user_id] = response.data;
              })
              .catch(erro => {
                console.error(`Error fetching user with ID ${post.user_id}:`, erro); // Log the error for debugging
                return Promise.reject({ status: 608, message: 'Erro na obtenção do utilizador', error: erro });
              })
          );
        }
        // Fetch ruas if not already fetched
        if (post.rua_id && !ruasMap[post.rua_id]) {
          ruaPromises.push(
            axios.get('http://api:3000/ruas/' + post.rua_id, {
              headers: {
                Authorization: token
              }
            })
              .then(response => {
                ruasMap[post.rua_id] = response.data;
              })
              .catch(erro => {
                console.error(`Error fetching rua with ID ${post.rua_id}:`, erro);
                return Promise.reject({ status: 608, message: 'Erro na obtenção da rua', error: erro });
              })
          );
        }
        // Fetch comments
        commentPromises.push(
          axios.get('http://api:3000/posts/comments/' + post._id, {
            headers: {
              Authorization: token
            }
          })
            .then(response => {
              commentsMap[post._id] = response.data;
            })
            .catch(erro => {
              console.error(`Error fetching comments for post with ID ${post._id}:`, erro);
              return Promise.reject({ status: 608, message: 'Erro na obtenção dos comentários', error: erro });
            })
        );
      });

      return Promise.all([...userPromises, ...ruaPromises, ...commentPromises])
        .then(() => {
          const formattedPosts = posts.map(post => {
            if (!post) {
              console.warn('Null or undefined post found during formatting:', post);
              return null;
            }

            const user = usersMap[post.user_id];
            const rua = ruasMap[post.rua_id];
            const comentarios = commentsMap[post._id] || [];

            if (!user) {
              console.warn(`User not found for post ID: ${post._id}, user ID: ${post.user_id}`);
            }
            if (!rua) {
              console.warn(`Rua not found for post ID: ${post._id}, rua ID: ${post.rua_id}`);
            }

            return {
              _id: post._id,
              data: post.data,
              desc: post.desc,
              comentarios: comentarios
                .filter(comment => comment !== null)
                .map(comment => {
                  const commentUser = usersMap[comment.user_id];

                  if (!commentUser) {
                    console.warn(`User not found for comment ID: ${comment._id}, user ID: ${comment.user_id}`);
                  }

                  return {
                    _id: comment._id,
                    data: comment.data,
                    comentario: comment.comentario,
                    user: commentUser ? {
                      _id: commentUser._id,
                      username: commentUser.username
                    } : null
                  };
                }),
              user: user ? {
                _id: user._id,
                username: user.username,
                registo: user.registo
              } : null,
              rua: rua ? {
                _id: rua._id,
                nome: rua.nome
              } : null
            };
          }).filter(post => post !== null);

          console.log('Formatted posts:', formattedPosts);

          res.status(200).render('posts', { posts: formattedPosts, ruas: ruas, d: date });
        });
    })
    .catch(erro => {
      console.error('Error fetching posts or ruas:', erro);
      if (erro.status) {
        res.status(erro.status).render('error', { message: erro.message, error: erro.error });
      } else {
        res.status(500).render('error', { message: 'Erro na obtenção dos posts', error: erro });
      }
    });
});




/* GET page to addPost */
router.get('/posts/add', auth.verificaAcesso(['user', 'admin']), function(req, res, next) {
  var date = new Date().toISOString().substring(0,16);
  
  const token = req.cookies.token;

  // Fetch all ruas
  axios.get('http://api:3000/ruas', {
    headers: {
      Authorization: token
    }
  })
  .then(response => {
    const ruas = response.data;
    res.status(200).render('addPost', { ruas: ruas, d: date });
  })
  .catch(erro => {
    res.status(612).render('error', { message: 'Erro a tentar obter a página addPost', error: erro });
  });
});


router.post('/posts/add', auth.verificaAcesso(['user', 'admin']), function(req, res, next){
  var date = new Date().toISOString().substring(0,16);

  var newPost = {
    rua_id: req.body.rua_id,
    user_id: req.user.sub,
    data: date,
    desc: req.body.desc,
    comentarios: []
  };

  console.log(newPost);

  axios.post('http://api:3000/posts', newPost)
    .then(response => {
      res.status(201).redirect('/posts');
    })
    .catch( erro => {
      res.status(613).json({message: 'Erro ao criar um post', error: erro.message});
    });
});

/* POST comentário no post */
router.post('/posts/:idPost/comment', auth.verificaAcesso(['user', 'admin']), function(req, res, next) {
  var date = new Date().toISOString().substring(0,16);
  const comentario = {
    user_id: req.user.username,
    post_id: req.params.idPost,
    data: date,
    comentario: req.body.comentario
  };

  console.log(comentario)
  console.log('fiz o comment')

  axios.put(`http://api:3000/posts/${req.params.idPost}/comment`, comentario)
    .then(response => res.status(200).redirect(`/posts/${req.params.idPost}`))
    .catch(erro => res.status(619).render('error', {message: 'Não foi possível adicionar o comentário', error:erro}));
});


/* GET página da rua */
router.get('/ruas/:idRua', function(req, res, next){
  var date = new Date().toISOString().substring(0,16);
  var authorized = false;
  var admin = false;
  console.log(req.cookies.token);
  if(req.cookies.token) authorized = true;
  if(auth.verificaAcesso('admin')) admin = true;

  axios.get('http://api:3000/ruas/' + req.params.idRua)
    .then(response => {
      res.status(200).render('rua', {
        rua: response.data,
        isAuthorized: authorized,
        isAdmin: admin,
        d: date
      })
    })
    .catch( erro => {
      res.status(624).render('error', { message: 'Não foi possível obter a rua', error: erro});
    });
});


// Route to get images from API server
router.get('/images/:filename/:imagename', cacheMiddleware);

/* GET login page */
router.get('/login', function(req, res, next) {
  var date = new Date().toISOString().substring(0,16);
  res.status(200).render('login', {d: date})
});

/* POST login page */
router.post('/login', function(req, res, next) {
  console.log('Login request body:', req.body);
  axios.post('http://api:3000/users/login', req.body)
    .then(response => {
      console.log('Login response:', response.data);
      if (response.data.token) {
        res.cookie('token', response.data.token, { 
          secure: true, 
          httpOnly: true, 
          maxAge: 1900000 
        });
        res.status(200).redirect('/ruas');
      } else {
        res.status(401).send('<script>alert("Authentication failed: No token received."); window.location.href = "/login"; </script>');
      }
    })
    .catch(error => {
      console.error('Login error:', error.response ? error.response.data : error.message);
      res.status(401).send('<script>alert("Username ou palavra passe incorretas. Por favor introduza novamente."); window.location.href = "/login"; </script>');
    });
});



/* GET página para se registar */
router.get('/registo', function(req, res, next){
  var date = new Date().toISOString().substring(0,16);
  res.status(200).render('registar', {d:date})
});

/* POST registo */
router.post('/registo', function(req, res, next) {
  const formData = new FormData();
  
  console.log(req.body);
  for (key in req.body) {
    var value = req.body[key]
    if (Array.isArray(value)) {
      for (i in value) {
        formData.append(key + '[]', value[i]);
      }
    }
    else {
      formData.append(key, value);
    }
  }
  console.log(formData);

  axios({
    method: 'post',
    url: 'http://api:3000/users/register',
    data: formData,
    headers: {
      ...formData.getHeaders(),
    }
  })
  .then(response => {
    console.log("Registro realizado com sucesso:", response.data);
    res.status(200).redirect("/login");
  })
  .catch(error => {
    console.error("Erro no registro:", error);
    // Tratamento de erro genérico
    res.status(401).send('<script>alert("Erro no registo. Tente novamente."); window.location.href = "/registo"; </script>');
  });
});


/* GET perfil */
router.get('/perfil/', auth.verificaAcesso(['user', 'admin']), function(req, res, next) {
  var date = new Date().toISOString().substring(0, 16);

  // Get the user ID from the authenticated user's token
  const token = req.cookies.token;
  const decodedToken = jwt.decode(token);
  const userId = decodedToken.sub;

  console.log(userId);

  // Fetch the user information
  axios.get(`http://api:3000/users/${userId}`, { headers: { Authorization: token } })
    .then(userResponse => {
      const user = userResponse.data.dados;
      console.log(user);

      // Fetch the posts made by the user
      axios.get(`http://api:3000/posts/user/${userId}`)
        .then(postsResponse => {
          const posts = postsResponse.data;
          console.log(posts);

          // Fetch the associated "rua" information for each post
          const ruaPromises = posts.map(post => {
            return axios.get(`http://api:3000/ruas/${post.rua_id}`)
              .then(ruaResponse => {
                return { ...post, rua: ruaResponse.data, user: user };
              })
              .catch(erro => {
                throw new Error('Erro a obter a rua associada ao post.');
              });
          });

          Promise.all(ruaPromises)
            .then(formattedPosts => {
              res.status(200).render('perfil', {
                user: user,
                isAdmin: user.level === 'admin',
                posts: formattedPosts,
                d: date
              });
            })
            .catch(erro => res.status(632).render('error', { message: erro.message, error: erro }));
        })
        .catch(erro => res.status(633).render('error', { message: 'Erro a obter os posts', error: erro }));
    })
    .catch(erro => res.status(628).render('error', { message: 'Sessão Expirada. Por favor faça login novamente.', error: erro }));
});


/* GET edit perfil */
router.get('/perfil/edit', function(req, res, next) {
  var data = new Date().toISOString().substring(0,16).replace('T',' ')
  var token = req.cookies.token;
  var admin = false;
  const decodedToken = jwt.decode(token);
  const userId = decodedToken.sub;

  console.log(userId);


  axios.get(`http://api:3000/users/${userId}`,{headers: {authorization: token}})
  .then(response =>{
    const user = response.data.dados;
    if (user.level == 'administrador') admin = true
    console.log(user)
    res.status(200).render('editPerfil', {user:user, isAdmin:admin, d:data})
  })
  .catch(erro => res.status(629).render('error', { message: 'Não foi possível aceder à edição do utilizador', error:erro}))
});

router.post('/perfil/edit',upload.none(), function(req, res, next){
  const formData = new FormData();
  const userId = req.body.user_id;

  console.log(userId)
  console.log(req.body)

  Object.keys(req.body).forEach(key => {
    const value = req.body[key];
    if(Array.isArray(value)) {
      value.forEach(item => formData.append(`${key}[]`, item));
    } else {
      formData.append(key, value);
    }
  });

  console.log(formData)

  axios.put(`http://api:3000/users/${userId}`, formData, {
    headers: {
      authorization: req.cookies.token,
      ...formData.getHeaders()
    }
  })
  .then(response => {
    res.status(200).redirect("/perfil/");
  })
  .catch(erro => {
    res.status(630).render('error', {message: 'Não foi possível atualizar o seu perfil', error: erro});
  });
});


/* LOGOUT */
router.get('/logout',function(req, res, next) {
  res.clearCookie('token')
  res.status(200).redirect("/")
})
  module.exports = router;


/* DELETE rua */
router.get('/ruas/delete/:idRua',auth.verificaAcesso('admin'), function(req, res) {
  axios.delete("http://api:3000/ruas/delete/"+ req.params.idRua)
  .then(response => {
    res.redirect('/ruas')
  })
  .catch(err => {
    res.status(607).render('error', {error: err})
  })
});

module.exports = router;


/* DELETE post */
router.get('/posts/delete/:idPost', auth.verificaAcesso(['user', 'admin']), function(req, res, next) {
  axios.delete(`http://api:3000/posts/delete/${req.params.idPost}`)
    .then(response => res.status(200).redirect('/posts'))
    .catch(erro => res.status(500).render('error', {message: 'Não foi possível remover o post', error: erro}));
});


/* GET post */
// Rota para visualizar um post específico
router.get('/posts/:idPost', auth.verificaAcesso(['user', 'admin']), function(req, res, next) {
  var date = new Date().toISOString().substring(0, 16);

  // Get the post ID from the request parameters
  const postId = req.params.idPost;
  const token = req.cookies.token;

  const isAdmin = req.user && req.user.level === 'admin';
  console.log(isAdmin);

  // Fetch the post details
  axios.get(`http://api:3000/posts/${postId}`, { headers: { Authorization: token } })
    .then(postResponse => {
      const post = postResponse.data;

      // Fetch the user who created the post
      axios.get(`http://api:3000/users/${post.user_id}`, { headers: { Authorization: token } })
        .then(userResponse => {
          const user = userResponse.data;
          console.log(user)

          // Fetch the street associated with the post
          axios.get(`http://api:3000/ruas/${post.rua_id}`, { headers: { Authorization: token } })
            .then(ruaResponse => {
              const rua = ruaResponse.data;

              // Renderizar o template com isAdmin e outras informações
              res.status(200).render('post', {
                post: post,
                user: user,
                rua: rua,
                d: date,
                isAdmin: isAdmin 
              });
            })
            .catch(erro => res.status(636).render('error', { message: 'Erro a obter a rua associada ao post', error: erro }));
        })
        .catch(erro => res.status(635).render('error', { message: 'Erro a obter o utilizador do post', error: erro }));
    })
    .catch(erro => res.status(634).render('error', { message: 'Erro a obter o post', error: erro }));
});


/* DELETE comentário  */
router.get('/posts/:idPost/delete/:idComment', auth.verificaAcesso('admin'), function(req, res, next) {
  axios.delete(`http://api:3000/posts/delete/${req.params.idPost}/comment/${req.params.idComment}`)
    .then(response => res.status(200).redirect(`/posts/${req.params.idPost}`))
    .catch(erro => res.status(500).render('error', {message: 'Não foi possível remover o comentário', error: erro}));
});
