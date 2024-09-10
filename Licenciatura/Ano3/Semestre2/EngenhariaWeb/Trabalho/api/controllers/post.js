var Post = require('../models/post');
var Rua = require('../models/rua');

module.exports.list = () => {
    return Post
        .find()
        .sort({rua_id: 1})
        .exec()
}

module.exports.findById = id => {
    return Post
        .findOne({_id: id})
        .exec()
}

module.exports.findByUserId = userId => {
    return Post
        .find({ user_id: userId })
        .exec();
}

module.exports.findCommentsByPostId = postId => {
    return Post
        .findOne({_id: postId}, 'comentarios')
        .exec()
        .then(post => post ? post.comentarios : []);
}

module.exports.insert = async post => {
    try {
        const existingPost = await Post.findOne({ _id: post._id }).exec();
        if (existingPost) {
        throw new Error('Post with this ID already exists');
        }

        const ruaExists = await Rua.findOne({ _id: post.rua_id }).exec();
        if (!ruaExists) {
        throw new Error('Specified rua does not exist');
        }

        const newPost = new Post(post);
        return await newPost.save();
    } catch (error) {
        throw new Error(`Error inserting post: ${error.message}`);
    }
};

module.exports.update = (id, post) => {
    return Post
        .findByIdAndUpdate(id, post, {new : true})
        .exec()
}

module.exports.remove = id => {
    return Post
        .findByIdAndDelete(id)
        .exec()
}

module.exports.removeC = (id,commentId) => {
    return Post
        .findById(id)
        .then(post => {
            post.comentarios = post.comentarios.filter(comment => comment._id != commentId)
            return post.save()
        })
}

module.exports.addComment = (id, comment) => {
    return Post
        .findById(id)
        .then(post => {
            post.comentarios.push(comment)
            return post.save()
        })
}

module.exports.getNextPostId = async () => {
    try {
        const lastPost = await Post.findOne().sort({ _id: -1 }).exec();
        return lastPost ? lastPost._id + 1 : 1;
    } catch (error) {
        console.error('Error fetching the last post:', error);
        throw new Error('Error fetching the last post');
    }
};

module.exports.getNextCommentId = async () => {
    try {
        const lastComment = await Post.aggregate([
            { $unwind: "$comentarios" },
            { $sort: { "comentarios._id": -1 } },
            { $limit: 1 },
            { $project: { _id: "$comentarios._id" } }
        ]).exec();

        return lastComment.length ? lastComment[0]._id + 1 : 1;
    } catch (error) {
        console.error('Error fetching the last comment:', error);
        throw new Error('Error fetching the last comment');
    }
};