
const express = require('express');
const config = require('./config/init');

const bodyParser = require('body-parser');
const toolsRoutes = require('./api/routes/tools');

const app = express();

config.initializeDB();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(config.cors);

app.use('/tools', toolsRoutes);

module.exports = app;