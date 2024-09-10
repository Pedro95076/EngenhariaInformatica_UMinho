var mongoose = require('mongoose')

var commentSchema = new mongoose.Schema({
    _id: Number,
    post_id: Number,
    user_id: String,
    comentario: String,
    data: Date,
})

var postSchema = new mongoose.Schema({
    _id: Number,
    rua_id: Number,
    user_id: String,
    data: Date,
    desc: String,
    comentarios: [commentSchema],
})

module.exports = mongoose.model('posts', postSchema)