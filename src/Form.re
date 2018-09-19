/* 
построить алгебру простых компонентов: 
    поле ввода текста, 
    после ввода числа, 
    флажок, 
    radio кнопка и кнопка. 
К компонентам можно опционально добавить валидацию: 
    поле не может быть пустым и 
    значение поля не должно превышать размер n. */
 /* 
    let xs = [
     InputText("nameOfInput",[NotEmpty, MaxLength(12)]),
     Button("Send form!",[])
    ];
    render(xs); 
*/

type component =
    | InputText(string)
    | Button(string)

let list = [InputText("nameOfInput"),Button("Send form!")];
/* 
let form =
    switch (list) {
        | [] => "This list is empty"
        | [InputText(name), ...rest] => "<input name='" ++ name ++"'/>"
        | [Button(text)] => "<button>" ++ text ++ "</button>"
    }; */

let component = ReasonReact.statelessComponent("Form");

let make = (~name, _children) => {
    ...component,

    render: _self =>{
        ReactDOMRe.createElement("form", [|
            <p>(ReasonReact.string(name))</p>,
            <button>(ReasonReact.string(name))</button>
        |]);
    },
};