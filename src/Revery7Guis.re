open Revery;
open Revery.UI;
open Revery.UI.Components;

type example = {
  name: string,
  render: unit => React.element(React.node),
};

let examples = [
  {name: "1. Counter", render: () => Counter.render()},
  {name: "2. Temp. Converter", render: () => TempConverter.render()},
];

let getExampleByName = (name: string) =>
  List.find(ex => ex.name == name, examples);

module ExampleListItem = {
  let make = (~isActive, ~example, ~onClick, ()) => {
    let bgColor =
      isActive ? StyleColors.selectedColor : Colors.transparentWhite;
    let textColor = isActive ? Colors.white : Colors.black;

    let textStyle =
      Style.[
        color(textColor),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(14),
        margin(16),
      ];

    let itemStyle = Style.[backgroundColor(bgColor)];

    <View style=itemStyle>
      <Clickable onClick>
        <Text style=textStyle text={example.name} />
      </Clickable>
    </View>;
  };
};

module ExampleHost = {
  let%component make = (~window as win, ()) => {
    let%hook (currentExample, setCurrentExample) =
      Hooks.state(List.nth(examples, 0));

    let renderListItem = (ex: example) => {
      let isActive = currentExample.name == ex.name;
      <ExampleListItem
        isActive
        example=ex
        onClick={
          _ => {
            Window.setTitle(win, "Revery 7GUIs -- " ++ ex.name);
            setCurrentExample(_ => ex);
          }
        }
      />;
    };

    let exampleListItems = List.map(renderListItem, examples);

    <View
      onMouseWheel={_evt => ()}
      style=Style.[
        position(`Absolute),
        justifyContent(`Center),
        alignItems(`Center),
        backgroundColor(StyleColors.bgColor),
        bottom(0),
        top(0),
        left(0),
        right(0),
        flexDirection(`Row),
      ]>
      <ScrollView
        style=Style.[
          position(`Absolute),
          top(0),
          left(0),
          width(175),
          bottom(0),
          borderRight(~width=1, ~color=Colors.darkGray),
          backgroundColor(StyleColors.bgColor),
        ]>
        <View> {exampleListItems |> React.listToElement} </View>
      </ScrollView>
      <View
        style=Style.[
          position(`Absolute),
          top(0),
          left(175),
          right(0),
          bottom(0),
          backgroundColor(StyleColors.bgColor),
        ]>
        {currentExample.render()}
      </View>
    </View>;
  };
};

let init = app => {
  let windowWidth = 800;
  let windowHeight = 480;

  let win =
    App.createWindow(
      ~createOptions=
        WindowCreateOptions.create(
          ~width=windowWidth,
          ~height=windowHeight,
          (),
        ),
      app,
      "Revery 7GUIs",
    );

  if (Environment.webGL) {
    Window.maximize(win);
    ();
  } else {
    Window.center(win);
    ();
  };

  let _ = UI.start(win, <ExampleHost window=win />);
  ();
};

App.start(init);
