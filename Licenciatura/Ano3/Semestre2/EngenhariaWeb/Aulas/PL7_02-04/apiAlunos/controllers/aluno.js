const mongoose = require('mongoose')
const { modelName } = require("../models/aluno")
var Aluno = require("../models/aluno")

module.exports.list = () => {
    return Aluno
        .find()
        .sort({nome : 1})
        .exec()
}

module.exports.findById = id => {
    return Aluno
        .findOne({_id : id})
        .exec()
}

module.exports.findAlunoTpcById = id => {
    return Aluno
        .findOne({_id : id})
        .select('tpc1 tpc2 tpc3 tpc4 tpc5 tpc6 tpc7 tpc8')
        .exec()
}

module.exports.listAllIfTpc = id => {
    tpc = `tpc${id}`
    filtro = {}
    filtro[tpc] = true
    return Aluno
        .find(filtro)
        .sort({nome : 1})
        .exec()
}

module.exports.insert = aluno => {
    if((Aluno.find({_id : aluno._id}).exec()).length != 1){
        var newAluno = new Aluno(aluno)
        return newAluno.save()
    }
}

module.exports.update = (id, aluno) => {
    return Aluno
        .findByIdAndUpdate(id, aluno, {new : true})
        .exec()
}


module.exports.invertTpc = (idAluno, idTpc) => {
    return Aluno
        .findOne({'_id' : idAluno})
        .exec()
        .then( aluno => {
            tpc = `tpc${idTpc}`
            if(aluno[tpc]){
                aluno[tpc] = !aluno[tpc]
            }else{
                aluno[tpc] = true
            }

            return Aluno
                .findByIdAndUpdate(idAluno, aluno, {new : true})
                .exec()
        })
}

module.exports.remove = id => {
    return Aluno
        .findByIdAndDelete(id)
        .exec()
}