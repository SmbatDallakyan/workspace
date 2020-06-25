class View {
    constructor() {
        this.table = this.getElement('#tools_table');
    }

    createElement(tag, className) {
      const element = document.createElement(tag)
      if (className) element.classList.add(className)

      return element
    }

    getElement(selector) {
        const element = document.querySelector(selector)
        return element
    }


    displayToolList(tool_list) {
        const table = this.getElement('#tools_table');
        console.log(table.childNodes[3]);
        if (table.childNodes[3]) {
            table.removeChild(table.childNodes[3]);
        }

        const table_body = this.createElement('tbody');

        tool_list.forEach(tool => {
            const row = table_body.insertRow();
            const cell_name = row.insertCell();
            const cell_status = row.insertCell();
            const cell_commands = row.insertCell();
            cell_name.innerHTML = tool.name;
            cell_status.innerHTML = tool.status;
            cell_commands.innerHTML = tool.commands;

        });

        table.appendChild(table_body);
        console.log(tool_list);
    }

    bindAddTool = handler => {
        // this.form.addEventListener('submit', event => {
        //     event.preventDefault()
        //     handler("TODO get list");
        // });
    }
}



class Model {
    constructor() {
        this.tools_list = {};
        this.server = new Server();
        this._getToolList();
    }

    _setToolList(tool_list) {
        this.tools_list = tool_list;
        this.onToolListChanged(tool_list);
    }

    _getToolList = async () => {
        const new_list = await this.server.getAllTools();
        this._setToolList(new_list);
    }

    addTool = async (new_tool) => {
        await this.server.addNewTool(new_tool);
        _getToolList();
    }

    deleteTool = async (tool_id) => {
        await this.server.deleteTool(tool_id);
        _getToolList();
    }

    updateTool = async (tool) => {
        await this.server.updateTool(tool);
        _getToolList();
    }

    bindToolListChanged(callback) {
        this.onToolListChanged = callback
    }
}

class Controller {
    constructor(model, view) {
        this.model = model;
        this.view = view;

        this.view.bindAddTool(this.handleAddTools);
        this.model.bindToolListChanged(this.onToolListChanged);

        // this.onToolListChanged(this.model.tools_list);
    }

    onToolListChanged = tool_list => {
        this.view.displayToolList(tool_list);
    }

    handleAddTools = todoText => {
        if (todoText.length > 2) {
            this.model.addTool(todoText)
        } else {
            alert("Too short text")
        }
    }
}

class Server {
    constructor() {
        this.ax = axios.create({
            baseURL: 'http://localhost:3000',
            timeout: 1000,
        });
    }

    addNewTool = async (tool) => {
        try {
            const res = await this.ax.post(`/tools`, tool);
        } catch(e) {
            console.error(e);
        }
    }

    updateTool = async (tool) => {
        try {
            const res = await this.ax.put(`/tools/`, tool);
        } catch(e) {
            console.error(e);
        }
    }

    getAllTools = async () => {
        try {
            const res = await this.ax.get('/tools');
            return res.data.tools;
        } catch(e) {
            console.error(e);
            return null;
        }
    }

    deleteTool = async (tool_id) => {
        try {
            const res = await this.ax.delete(`/tools/${tool_id}`)
        } catch(e) {
            console.error(e);
        }
    }
}


const app = new Controller(new Model(), new View());