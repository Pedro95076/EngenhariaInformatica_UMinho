const mongoose = require('mongoose');

const periodoSchema = new mongoose.Schema({
    _id: String,
    nome: String,
    compositores: [{
        id: String,
        nome: String
    }]
});

module.exports = mongoose.model('periodo', periodoSchema)