var mongoose = require('mongoose')

var figuraSchema = new mongoose.Schema({
    id: String,
    figuraId: String,
    imagem: String,
    legenda: String,
})

var casaSchema = new mongoose.Schema({
    _id: String,
    enfiteuta: String,
    foro: String,
    desc: String,
})

var dataSchema = new mongoose.Schema({
    _id: Number,
    nome: String,
    rua: String,
})

var entidadeSchema = new mongoose.Schema({
    rua: Number,
    tipo: String,
    nome: String,
    posição: Number,
})

var lugarSchema = new mongoose.Schema({
    rua: Number,
    nome: String,
    posição: Number,
})

var ruaSchema = new mongoose.Schema({
    _id: Number,
    nome: String,
    para: [String],
    figuras: [figuraSchema],
    lista_casas: [casaSchema],
    datas: [dataSchema],
    entidades: [entidadeSchema],
    lugares: [lugarSchema],
})

module.exports = mongoose.model('ruas', ruaSchema)
