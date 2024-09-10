var express = require('express');
var router = express.Router();
var Rua = require('../controllers/rua');
var multer = require('multer');
var fs = require('fs');
var path = require('path');

var upload = multer({ dest: 'uploads' });

router.get('/images/:filename/:imagename', function(req, res, next) {
    const filename = req.params.filename;
    const imagename = req.params.imagename;
    const imagePath = path.join(__dirname, '../public', 'images', filename, imagename);
    
    fs.access(imagePath, fs.constants.F_OK, (err) => {
        if (err) {
            return res.status(404).send('Imagem não encontrada.');
        }
        res.status(200).sendFile(imagePath);
    });
});


/* Listar as Ruas (R) */
router.get('/', function (req, res) {
    if (req.query.ordem) {
        Rua.listOrdered(req.query.ordem)
        .then(data => res.jsonp(data))
        .catch(erro => res.status(500).jsonp({ error: 'Erro ao listar ruas ordenadas', details: erro }));
    } else if (req.query.elemento) {
        console.log("estive aqui")
        Rua.searchByElement(req.query.elemento)
        .then(data => res.jsonp(data))
        .catch(erro => res.status(500).jsonp({ error: 'Erro ao pesquisar ruas por elemento', details: erro }));
    } else {
        Rua.list()
        .then(data => res.jsonp(data))
        .catch(erro => res.status(500).jsonp({ error: 'Erro ao listar ruas', details: erro }));
    }
});

/* Consultar uma Rua (R) */
router.get('/:id', function (req, res) {
    Rua.findById(req.params.id)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro));
});

/* Criar uma Rua (C) */
router.post('/add', upload.array('imagens', 12), async function (req, res) {
    try {
        let figuras = [];
        let figuraIds = Array.isArray(req.body.figuraId) ? req.body.figuraId : (req.body.figuraId ? [req.body.figuraId] : []);
        let figuraUids = Array.isArray(req.body.id) ? req.body.id : (req.body.id ? [req.body.id] : []);
        let legendas = Array.isArray(req.body.legenda) ? req.body.legenda : (req.body.legenda ? [req.body.legenda] : []);

        console.log('figuraIds:', figuraIds);
        console.log('figuraUids:', figuraUids);
        console.log('legendas:', legendas);
        console.log('files:', req.files);

        // Check if figuraIds and figuraUids are not empty and have valid lengths
        if (figuraIds.length && figuraUids.length) {
            // Ensure the lengths of figuraIds, figuraUids, and legendas match the number of files
            if (figuraIds.length !== legendas.length || figuraIds.length !== req.files.length || figuraIds.length !== figuraUids.length) {
                return res.status(400).jsonp({ error: 'Mismatch between figuraUids, figuraIds, legendas, and files' });
            }

            for (let i = 0; i < figuraIds.length; i++) {
                const newFilePath = path.join('..', figuraIds[i], req.files[i].originalname);
                figuras.push({
                    id: figuraUids[i],
                    figuraId: figuraIds[i],
                    legenda: legendas[i],
                    imagem: newFilePath
                });

                console.log('Added figura:', figuras[i]);
            }
        }

        // Move the files to their new locations if figuras are constructed
        if (req.files && req.files.length > 0 && figuras.length > 0) {
            req.files.forEach((file, index) => {
                const oldPath = file.path;
                const newPath = path.join(__dirname,'..','public', 'images',figuras[index].figuraId, figuras[index].imagem);
                console.log(newPath)
                fs.mkdirSync(path.dirname(newPath), { recursive: true });
                fs.renameSync(oldPath, newPath);
                console.log('File moved to:', newPath);
            });
        }

        const datas = req.body.datas ? (Array.isArray(req.body.datas) ? req.body.datas : [req.body.datas]) : [];
        const lista_casas = req.body.lista_casas ? (Array.isArray(req.body.lista_casas) ? req.body.lista_casas : [req.body.lista_casas]) : [];
        const entidades = req.body.entidades ? (Array.isArray(req.body.entidades) ? req.body.entidades : [req.body.entidades]) : [];
        const lugares = req.body.lugares ? (Array.isArray(req.body.lugares) ? req.body.lugares : [req.body.lugares]) : [];

        const ruaId = await Rua.getNextRuaId();

        const rua = {
            _id: ruaId,
            nome: req.body.nome,
            para: Array.isArray(req.body.para) ? req.body.para : (req.body.para ? req.body.para.split(',') : []),
            figuras: figuras,
            lista_casas: lista_casas,
            datas: datas,
            entidades: entidades,
            lugares: lugares
        };

        Rua.insert(rua)
            .then(data => res.jsonp(data))
            .catch(erro => {
                console.error('Error inserting Rua:', erro);
                res.status(500).jsonp({ error: 'Error inserting Rua', details: erro });
            });
    } catch (error) {
        console.error('Error processing request:', error);
        res.status(400).jsonp({ error: 'Invalid JSON input', details: error.message });
    }
});

//* Alterar uma Rua (U) */
router.put('/edit/:id', upload.array('imagens', 12), function (req, res) {
    try {
        let figuras = [];
        let figuraIds = Array.isArray(req.body.figuraId) ? req.body.figuraId : (req.body.figuraId ? [req.body.figuraId] : []);
        let figuraUids = Array.isArray(req.body.id) ? req.body.id : (req.body.id ? [req.body.id] : []);
        let legendas = Array.isArray(req.body.legenda) ? req.body.legenda : (req.body.legenda ? [req.body.legenda] : []);

        console.log('figuraIds:', figuraIds);
        console.log('figuraUids:', figuraUids);
        console.log('legendas:', legendas);
        console.log('files:', req.files);

        if (figuraIds.length && figuraUids.length) {
            // Ensure the lengths of figuraIds, figuraUids, and legendas match the number of files
            if (figuraIds.length !== legendas.length || figuraIds.length !== req.files.length || figuraIds.length !== figuraUids.length) {
                return res.status(400).jsonp({ error: 'Mismatch between figuraUids, figuraIds, legendas, and files' });
            }

            for (let i = 0; i < figuraIds.length; i++) {
                const newFilePath = path.join('..', figuraIds[i], req.files[i].originalname);
                figuras.push({
                    id: figuraUids[i],
                    figuraId: figuraIds[i],
                    legenda: legendas[i],
                    imagem: newFilePath
                });

                console.log('Added figura:', figuras[i]);
            }
        }

        if (req.files && req.files.length > 0 && figuras.length > 0) {
            req.files.forEach((file, index) => {
                const oldPath = file.path;
                const newPath = path.join(__dirname,'..','public', 'images',figuras[index].figuraId, figuras[index].imagem);
                console.log(newPath)
                fs.mkdirSync(path.dirname(newPath), { recursive: true });
                fs.renameSync(oldPath, newPath);
                console.log('File moved to:', newPath);
            });
        }

        const datas = req.body.datas ? (Array.isArray(req.body.datas) ? req.body.datas : [req.body.datas]) : [];
        const lista_casas = req.body.lista_casas ? (Array.isArray(req.body.lista_casas) ? req.body.lista_casas : [req.body.lista_casas]) : [];
        const entidades = req.body.entidades ? (Array.isArray(req.body.entidades) ? req.body.entidades : [req.body.entidades]) : [];
        const lugares = req.body.lugares ? (Array.isArray(req.body.lugares) ? req.body.lugares : [req.body.lugares]) : [];

        const rua = {
            nome: req.body.nome,
            para: Array.isArray(req.body.para) ? req.body.para : (req.body.para ? req.body.para.split(',') : []),
            figuras: figuras,
            lista_casas: lista_casas,
            datas: datas,
            entidades: entidades,
            lugares: lugares
        };

        Rua.update(req.params.id, rua)
            .then(data => res.jsonp(data))
            .catch(erro => res.jsonp(erro));
    } catch (error) {
        console.error('Error processing request:', error);
        res.status(400).jsonp({ error: 'Invalid JSON input', details: error.message });
    }
});

router.delete('/delete/:id', function (req, res) {
    Rua.findById(req.params.id)
        .then((rua) => {
            rua.figuras.forEach(figura => {
                if (figura.imagem) {
                    const imagePath = path.join(__dirname, '..', figura.imagem);
                    if (fs.existsSync(imagePath)) {
                        fs.unlinkSync(imagePath);
                        console.log('Deleted file:', imagePath);
                    }
                }
            });
            return Rua.remove(req.params.id);
        })
        .then((result) => {
            console.log("Deleted rua:", req.params.id);
            res.jsonp(result);
        })
        .catch(erro => res.jsonp(erro));
});

module.exports = router;
