var Rua = require('../models/rua');

module.exports.list = () => {
  return Rua
    .find()
    .sort({ nome: 1 })
    .exec();
}

module.exports.findById = id => {
  return Rua
    .findOne({ _id: id })
    .exec();
}

module.exports.insert = async rua => {
  const existingRua = await Rua.findOne({ _id: rua._id }).exec();
  if (!existingRua) {
    var newRua = new Rua(rua);
    return newRua.save();
  } else {
    throw new Error('Rua already exists with this ID.');
  }
}

module.exports.update = (id, rua) => {
  return Rua
    .findByIdAndUpdate(id, rua, { new: true })
    .exec();
}

module.exports.remove = id => {
  return Rua
    .findByIdAndDelete(id)
    .exec();
}

module.exports.listOrdered = ordem => {
  const sortOptions = { nome: ordem === 'asc' ? 1 : -1 };
  return Rua
    .find()
    .sort(sortOptions)
    .exec();
}

module.exports.searchByElement = elem => {
    console.log("Searching with element:", elem);
    const regex = new RegExp(elem, 'i');
    let searchCriteria = [
      { nome: regex },
      { 'lugares.nome': regex },
      { 'entidades.nome': regex },
      { 'datas.nome': regex}
    ];
  
    console.log("Search criteria:", searchCriteria);
  
    return Rua
      .find({ $or: searchCriteria })
      .exec()
      .then(result => {
        console.log("Search result:", result);
        return result;
      })
      .catch(error => {
        console.error("Search error:", error);
        throw error;
      });
  }

module.exports.getNextRuaId = async () => {
    try {
        const lastRua = await Rua.findOne().sort({ _id: -1 }).exec();
        return lastRua ? lastRua._id + 1 : 1;
    } catch (error) {
        console.error('Error fetching the last Rua:', error);
        throw new Error('Error fetching the last Rua');
    }
}
