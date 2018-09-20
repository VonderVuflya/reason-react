type validator =
  | Required
  | MaxLength(int)
  | Value(string)
  | Placeholder(string)
  | ClassName(string);

type field =
  | InputText(string, list(validator))
  | InputNumber(string, list(validator))
  | Checkbox(string, list(validator))
  | RadioButton(string, list(validator))
  | Button(string, list(validator));

let generateValidaros = validators =>
  List.map(
    validator =>
      switch (validator) {
      | Required => ("required", "true")
      | MaxLength(count) => ("maxLength", count->string_of_int)
      | Value(text) => ("value", text)
      | Placeholder(text) => ("placeholder", text)
      | ClassName(text) => ("class", text)
      },
    validators,
  );

let generateInputs = (t: string, name: string, validators: list(validator)) => {
  let valid = validators->generateValidaros;
  let input = <input name type_=t />;

  ReasonReact.cloneElement(
    input,
    ~props=Obj.magic(Js.Dict.fromList(valid)),
    [||],
  );
};

let render = field =>
  switch (field) {
  | InputText(name, validators) => generateInputs("text", name, validators)
  | InputNumber(name, validators) =>
    generateInputs("number", name, validators)
  | Checkbox(name, validators) =>
    generateInputs("checkbox", name, validators)
  | RadioButton(name, validators) =>
    generateInputs("radio", name, validators)
  /* | Button(name, validators) => <input type_="submit" value=name /> */
  | Button(name, validators) => generateInputs("submit", name, validators)
  };

let xs = [
  InputText(
    "nameOfInput",
    [Required, MaxLength(3), Placeholder("Type text")],
  ),
  InputNumber(
    "numberName",
    [Required, MaxLength(4), Placeholder("Type a number")],
  ),
  Checkbox("checkBox", [Value("checkbox"), ClassName("left-input")]),
  RadioButton("radioButton", [ClassName("right-input")]),
  Button("", [Value("Send form!")]),
];

let result = List.map(render, xs); /* input => input-> */
Js.log(result);

let resultfunc = result->ArrayLabels.of_list->ReasonReact.array;

let component = ReasonReact.statelessComponent("Form");

let make = _children => {
  ...component,
  render: _self => <form> resultfunc </form>,
};