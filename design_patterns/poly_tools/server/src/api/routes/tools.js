const express = require('express');
var HttpStatus = require('http-status-codes');

const router = express.Router();
const toolController = require('../controllers/tool');


/*
* GET tool by id
*/
router.get('/:id', async (req, res, next) => {
    try {
        const tool = await toolController.getTool(req.params.id);
        const status = tool ? HttpStatus.OK : HttpStatus.NOT_FOUND;
        const message = tool ? 'tool found' : 'tool not found';
        res.status(status).json({
            message: message,
            tool: tool
        });
    } catch (e) {
        console.log(e.message);
        res.status(HttpStatus.INTERNAL_SERVER_ERROR).json({
            message: e.message
        });
    }
});


/*
* GET all Tools
*/
router.get('/', async (req, res, next) => {
    try {
        const tools = await toolController.getAllTools();
        res.status(HttpStatus.OK).json({
            message: 'All tools',
            tools: tools
        });
    } catch (e) {
        console.log(e.message);
        res.status(HttpStatus.NOT_FOUND).json({
            message: e.message
        });
    }
});

/*
* POST a new Tool
*/
router.post("/", async (req, res, next) => {
    try {
        const tool = await toolController.createNewTool(req.body);
        res.status(HttpStatus.CREATED).json({
            message: "Created successfully",
            tool
        });
    } catch (e) {
        console.log(e.message);
        res.status(HttpStatus.BAD_REQUEST).json({
            message: e.message,
        });
    }
});

/*
* Update Tool
*/
router.put("/", async (req, res, next) => {
    try {
        const tool = await toolController.updateTool(req.body);
        res.status(HttpStatus.OK).json({
            message: "Updated successfully",
            tool
        });
    } catch (e) {
        console.log(HttpStatus.BAD_REQUEST);
        res.status(e.status).json({
            message: e.message,
        });
    }
});

/*
* Delete Tool
*/
router.delete("/:id", async (req, res, next) => {
    try {
        const tool = await toolController.deleteTool(req.params.id);
        res.status(HttpStatus.OK).json({
            message: "Deleted",
            tool
        });
    } catch (e) {
        console.log(e.message);
        res.status(HttpStatus.BAD_REQUEST).json({
            message: e.message,
        });
    }
});

module.exports = router;