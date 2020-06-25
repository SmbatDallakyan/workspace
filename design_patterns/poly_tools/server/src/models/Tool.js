const mongoose = require('mongoose');
const toolSchema = mongoose.Schema({
    _id: mongoose.Schema.Types.ObjectId,
    name:   { type: String, required: true },
    status: { type: String, required: true },
    commands: { type: String, required: true },
});

module.exports = mongoose.model('Tool', toolSchema);