const mongoose = require('mongoose');
const Tool = require('../../models/Tool');

module.exports = {
    createNewTool: async (tool) => {
        const ID_KEY = '_id';
        if (ID_KEY in tool) {
            delete tool[ID_KEY]
        }
        const new_tool = new Tool(
            Object.assign(
                {},
                {ID_KEY: new mongoose.Types.ObjectId()},
                tool
            ));
        try {
            const newToolEntry = await new_tool.save()
            return newToolEntry;
        } catch (error) {
            throw error;
        }
    },

    updateTool: async (tool) => {
        const id = tool._id;
        try {
            const updatedToolEntry = await Tool.findByIdAndUpdate(id, tool);
            return updatedToolEntry;
        } catch (error) {
            throw error;
        }
    },

    deleteTool: async (id) => {
        try {
            const deletedToolEntry = await Tool.findByIdAndDelete(id);
            return deletedToolEntry;
        } catch (error) {
            throw error;
        }
    },

    getTool: async (id) => {
        try {
            const tool = await Tool.findById(id);
            return tool;
        } catch (error) {
            throw error;
        }
    },

    getAllTools: async() => {
        try {
            const tools = await Tool.find();
            return tools;
        } catch (error) {
            throw error;
        }
    }
}