var mongoose = require("mongoose")

var alunoSchema = new mongoose.Schema({
    _id : String,
    nome : String,
    gitlink : String,
    tpc1 : Boolean,
    tpc2 : Boolean,
    tpc3 : Boolean,
    tpc4 : Boolean,
    tpc5 : Boolean,
    tpc6 : Boolean,
    tpc7 : Boolean,
    tpc8 : Boolean,
    teste : Number,
    pratica : Number
}, { versionKey: false })

module.exports = mongoose.model('aluno', alunoSchema)