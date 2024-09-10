var Planta = require('../models/planta')

// GET /plantas
module.exports.list = () => {
    return Planta.find().sort({nome: 1})
        .then(dados => {
            return dados
        })
        .catch(erro => {
            return erro
        })

}

//GET /plantas/:id
module.exports.getPlanta = id => {
    return Planta.findOne({_id: id})
    .then(dados => {
        return dados
    })
    .catch(erro => {
        return erro
    })
}

//GET /plantas?especie=EEEE
module.exports.getPlantaEspecie = e => {
    return Planta.find({"Espécie": e})
    .then(dados => {
        return dados
    })
    .catch(erro => {
        return erro
    })
}

//GET /plantas?implant=AAA
module.exports.getPlantaImplant = i => {
    return Planta.find({"Implantação": i})
    .then(dados => {
        return dados
    })
    .catch(erro => {
        return erro
    })
}

//GET /plantas/freguesias
// lista ordenada sem repeticoes de freguesias
module.exports.getFreguesias = () => {
    return Planta.distinct("Freguesia").sort()
    .then(dados => {
        return dados
    })
    .catch(erro => {
        return erro
    })
}

//GET /plantas/especies
// lista ordenada sem repeticoes de especies
module.exports.getEspecies = () => {
    return Planta.distinct("Espécie").sort()
    .then(dados => {
        return dados
    })
    .catch(erro => {
        return erro
    })
}

//POST /plantas
// adicionar planta a db
module.exports.addPlanta = p => {
    return Planta.find({}, {_id: 1})
    .then(qtd => {
        var list = qtd.map( obj => {
            return {_id: obj._id};
        });

        list.sort((a,b) => parseInt(b._id) - parseInt(a._id));
        var next = parseInt(list[0]._id) + 1;
        p._id = next
        return Planta.create(p)
        .then(dados => {
            return dados
        })
        .catch(erro => {
            return erro
        })
    })
    .catch(erro => {
        return erro
    })
}

//put /plantas/:id
module.exports.updatePlanta = p => {
    return Planta.updateOne({_id: p._id}, p)
    .then(dados => {
        return dados
    })
    .catch(erro => {
        return erro
    })
}

//DELETE /plantas/:id
module.exports.deletePlanta = id => {
    return Planta.deleteOne({_id: id})
    .then(dados => {
        return dados
    })
    .catch(erro => {
        return erro
    })
}
