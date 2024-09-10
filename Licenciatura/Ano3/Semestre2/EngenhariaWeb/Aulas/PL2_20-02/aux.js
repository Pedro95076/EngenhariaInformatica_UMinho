// Data
exports.myDateTime = () => {
    var d = new Date().toISOString().substring(0,16)
    return d
}

// Nome
exports.myName = () => {
    return "Pedro Oliveira"
}

//Turma
exports.turma = "EngWeb2024::TP3"