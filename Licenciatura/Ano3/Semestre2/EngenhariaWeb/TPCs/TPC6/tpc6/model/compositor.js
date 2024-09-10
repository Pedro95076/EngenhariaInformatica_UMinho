var mongoose = require('mongoose')

var composerSchema = new mongoose.Schema({
    _id: String,
    nome : String,
    bio : String,
    dataNasc : String,
    dataObito : String,
    periodo : {
        id: String,
        nome : String
    }
}, {versionKey : false})

module.exports = mongoose.model('compositore', composerSchema)