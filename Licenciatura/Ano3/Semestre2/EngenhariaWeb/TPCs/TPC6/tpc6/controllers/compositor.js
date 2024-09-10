var mongoose = require("mongoose")
const { modelName } = require("../model/compositor")
var Compositor = require("../model/compositor")

module.exports.list = () => {
    return Compositor
        .find()
        .sort({nome:1})
        .exec()
}

module.exports.insert = (composer) => {
    if((Compositor.find({_id : composer._id}).exec()).length != 1){
        var novo = new Compositor(composer)
        return novo.save()
    }
}

module.exports.delete = (id) => {
    return Compositor
        .find({_id : id})
        .deleteOne()
        .exec()
}

module.exports.update = (id, Compositor) => {
    return Compositor
        .findByIdAndUpdate(id, Compositor, {new : true})
        .exec()
}