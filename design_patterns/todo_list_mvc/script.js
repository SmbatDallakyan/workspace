class View {
    constructor() {
        // The root element
        this.app = this.getElement('#root')

        this.title = this.createElement('h1')
        this.title.textContent = 'My Todo List'

        this.form = this.createElement('form')

        this.input = this.createElement('input')
        this.input.type = 'text'
        this.input.placeholder = 'Add todo'
        this.input.name = 'todo'

        this.submitButton = this.createElement('button')
        this.submitButton.textContent = 'Submit'

        this.todoList = this.createElement('ul', 'todo-list')

        this.form.append(this.input, this.submitButton)

        this.app.append(this.title, this.form, this.todoList)
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

    get _todoText() {
        return this.input.value;
    }

    _resetInput() {
        this.input.value = '';
    }

    displayTodoList(todo_list) {
        while (this.todoList.firstChild) {
            this.todoList.removeChild(this.todoList.firstChild);
        }

        if (todo_list.length == 0) {
            const p = this.createElement('p');
            p.textContent = 'List is empty';
            this.todoList.append(p);
        } else {
            todo_list.forEach(todo => {
                const li = this.createElement('li');
                li.id = todo.id;

                const span = this.createElement('span');
                span.textContent = todo.text;

                li.append(span);

                this.todoList.append(li);
            });

        }
    }

    bindAddTodo = handler => {
        this.form.addEventListener('submit', event => {
            event.preventDefault()
            if (this._todoText) {
                handler(this._todoText)
                this._resetInput()
            }
        });
    }

}

class Model {
    constructor(){
        this._id = 3;
        this.toDoList = [
            { id: 1, text: 'task 1' },
            { id: 2, text: 'task 2' }
        ]
    }

    addTodo(text) {
        const newTodo = {
            id: this._id++,
            text: text,
        }
        this.toDoList.push(newTodo);
        this.onTodoListChanged(this.toDoList);
    }

    bindTodoListChanged(callback) {
        this.onTodoListChanged = callback
    }

}

class Controller {
    constructor(model, view) {
        this.model = model;
        this.view = view;

        this.view.bindAddTodo(this.handleAddTodo);
        this.model.bindTodoListChanged(this.onTodoListChanged);

        this.onTodoListChanged(this.model.toDoList);
    }

    onTodoListChanged = todo_list => {
        this.view.displayTodoList(todo_list);
    }

    handleAddTodo = todoText => {
        if (todoText.length > 2) {
            this.model.addTodo(todoText)
        } else {
            alert("Too short text")
        }
    }
}

const app = new Controller(new Model(), new View());