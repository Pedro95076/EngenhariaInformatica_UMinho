var mongoose = require("mongoose")
const { modelName } = require("../model/periodo")
var Periodo = require("../model/periodo")

module.exports.list = () => {
    return Periodo
        .find()
        .sort({nome:1})
        .exec()
}

module.exports.insert = (period) => {
    if((Periodo.find({_id : period._id}).exec()).length != 1){
        var novo = new Periodo(period)
        return novo.save()
    }
}

module.exports.delete = (id) => {
    return Periodo
        .find({_id : id})
        .deleteOne()
        .exec()
}

module.exports.update = (id, period) => {
    return Periodo
        .findByIdAndUpdate(id, period, {new : true})
        .exec()
}