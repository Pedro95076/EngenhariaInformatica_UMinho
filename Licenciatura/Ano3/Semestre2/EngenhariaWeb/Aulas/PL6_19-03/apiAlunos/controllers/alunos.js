var mongoose = require("mongoose");

const { modelName } = require("../models/alunos");
var aluno = require("../models/alunos");

// Listar os alunos (GET)
module.exports.list = () => {
    return aluno.find().sort({ nome: 1 }).exec();
};

// Insere um aluno (POST)
module.exports.post = () => {
    var newAluno = new Aluni(aluno);
    return newAluno.save();
};

// Update (PUT)
module.exports.put = (id, alunoi) => {
    return aluno.findByIdAndUpdate(id, aluno, { new: true }).exec();
};

// Remove (DELETE)
module.exports.remove = (id) => {
    return aluno.findByIdAndDelete(id).exec();

    // Alternativa:
    /*
    aluno.find({ _id: id }).deleteOne().exec(})
    */
};
