class View {
    constructor() {
        this.table = this.getElement('#tools_table');
        this.btn_add_row = this.getElement('#btn_add_row');
        this.btn_add_row.addEventListener("click", this._add_empty_row);
    }

    _add_empty_row = () => {
        const table = this.table;
        let table_body = {};

        if (table.childNodes[3]) {
            table_body = table.childNodes[3];
        } else {
            table_body = this.createElement('tbody');
            table.appendChild(table_body);
        }

        const row = table_body.insertRow();
        row.insertCell(); /* name */
        row.insertCell(); /* status */
        row.insertCell(); /* commands */
        const cell_actions = row.insertCell();
        this._create_action_buttons(cell_actions);

        row.addEventListener('focusout', this._handle_focus_out, event);
        row.contentEditable = true;
    }

    createElement(tag, classNames) {
        const element = document.createElement(tag)
        if (classNames) {
            classNames.forEach(className => {
                element.classList.add(className)
            });
        }

      return element
    }

    getElement(selector) {
        const element = document.querySelector(selector)
        return element
    }

    _get_row_content(row) {
        const result = {};

        if (row.id) {
            result._id = row.id;
        }
        result.name = row.cells[0].innerText;
        result.status = row.cells[1].innerText;
        result.commands = row.cells[2].innerText;
        return result;
    }

    _handle_focus_out = (event) => {
        const changed_row = this._get_row_content(event.target);
        this.on_add_update_tool(changed_row);
    }

    _handle_delete_click = (event) => {
        event.stopPropagation();
        const id = event.target.parentElement.parentElement.getAttribute('id');
        this.on_delete_tool(id);
    }

    _create_action_buttons(parent) {
        const delete_button = this.createElement("button", ["btn", "btn-danger", "btn-rounded"]);
        delete_button.innerHTML = "Remove";
        delete_button.addEventListener("click", this._handle_delete_click, event);

        parent.appendChild(delete_button);
    }

    displayToolList(tool_list) {
        const table = this.getElement('#tools_table');

        if (!table) {
            return;
        }

        /* Clear table content */
        if (table.childNodes[3]) {
            console.log("Clear", table.childNodes[3]);
            table.removeChild(table.childNodes[3]);
        }

        const table_body = this.createElement('tbody');
        tool_list.forEach(tool => {
            const row = table_body.insertRow();
            const cell_name = row.insertCell();
            const cell_status = row.insertCell();
            const cell_commands = row.insertCell();
            const cell_actions = row.insertCell();

            cell_name.innerHTML = tool.name;
            cell_status.innerHTML = tool.status;
            cell_commands.innerHTML = tool.commands;

            row.setAttribute('id', tool._id);
            row.addEventListener('focusout', this._handle_focus_out, event);
            row.contentEditable = true;

            this._create_action_buttons(cell_actions);
        });

        table.appendChild(table_body);
        console.log(tool_list);
    }

    /* Bind */
    bindAddUpdateTool = handler => {
        this.on_add_update_tool = handler;
    }

    bindDeleteTool = handler => {
        this.on_delete_tool = handler;
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
        this._getToolList();
    }

    deleteTool = async (tool_id) => {
        await this.server.deleteTool(tool_id);
        this._getToolList();
    }

    updateTool = async (tool) => {
        await this.server.updateTool(tool);
        this._getToolList();
    }

    bindToolListChanged(callback) {
        this.onToolListChanged = callback
    }
}

class Controller {
    constructor(model, view) {
        this.model = model;
        this.view = view;

        this.view.bindAddUpdateTool(this.handleAddUpdateTool);
        this.view.bindDeleteTool(this.handleDeleteTool);

        this.model.bindToolListChanged(this.onToolListChanged);
    }

    onToolListChanged = tool_list => {
        this.view.displayToolList(tool_list);
    }

    handleAddUpdateTool = new_tool => {
        if (new_tool._id) {
            this.model.updateTool(new_tool);
        } else {
            this.model.addTool(new_tool);
        }
    }

    handleDeleteTool = id => {
        this.model.deleteTool(id);
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