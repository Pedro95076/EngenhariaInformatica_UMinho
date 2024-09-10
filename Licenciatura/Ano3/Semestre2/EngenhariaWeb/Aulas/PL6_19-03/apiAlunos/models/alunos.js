var mongoose = require("mongoose");

var alunosSchema = new mongoose.Schema(
    {
        _id: {
            type: String,
            required: true,
        },
        nome: String,
        gitLink: String,
        tpc1: Boolean,
        tpc2: Boolean,
        tpc3: Boolean,
        tpc4: Boolean,
        tpc5: Boolean,
        tpc6: Boolean,
        tpc7: Boolean,
        tpc8: Boolean,
        teste: Number,
        pratica: Number,
    },
    { versionKey: false }
);

module.exports = mongoose.model("alunos", alunosSchema); // A Collection alunos vai ser traduzida pelo alunosSchema
