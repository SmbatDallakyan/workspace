const mongoose = require('mongoose');
const { mongoUrl } = require('./index');

module.exports = {
    initializeDB: async () => {
        mongoose.set('useFindAndModify', false);
        mongoose.set('useNewUrlParser', true);
        mongoose.set('useUnifiedTopology', true);
        mongoose.connect(mongoUrl);
        mongoose.Promise = global.Promise;
    },

    cors: async (req, res, next) => {
        res.header("Access-Control-Allow-Origin", "*");
        res.header(
            "Access-Control-Allow-Headers",
            "Origin, X-Requested-With, Content-Type, Accept, Authorization"
        );

        if (req.method === "OPTIONS") {
            res.header("Access-Control-Allow-Methods", "PUT, POST, DELETE, GET");
            return res.status(200).json({});
        }
        next();
    }
}