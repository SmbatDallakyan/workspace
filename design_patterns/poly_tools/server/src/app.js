
const express = require('express');
const app = express();

const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const { mongoUrl } = require('./config');

//routes
const toolsRoutes = require('./api/routes/tools');

mongoose.set('useFindAndModify', false);
mongoose.set('useNewUrlParser', true);
mongoose.set('useUnifiedTopology', true);
mongoose.connect(mongoUrl);
mongoose.Promise = global.Promise;

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.use((req, res, next) => {
    res.header("Access-Control-Allow-Origin", "*");
    res.header(
    	"Access-Control-Allow-Headers",
      	"Origin, X-Requested-With, Content-Type, Accept, Authorization"
    );

	if (req.method === "OPTIONS") {
      	res.header("Access-Control-Allow-Methods", "PUT, POST, PATCH, DELETE, GET");
      	return res.status(200).json({});
    }
    next();
});

app.use('/tools', toolsRoutes);

module.exports = app;