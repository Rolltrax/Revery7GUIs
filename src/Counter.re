open Revery;
open Revery.UI;
open Revery.UI.Components;

module Example = {
  let%component make = () => {
    let%hook (count, setCount) = Hooks.state(0);

    let containerStyle =
      Style.[
        position(`Absolute),
        justifyContent(`Center),
        alignItems(`Center),
        bottom(0),
        top(0),
        left(0),
        right(0),
      ];

    let countStyle =
      Style.[
        fontSize(14),
        color(Colors.black),
        fontFamily("Roboto-Regular.ttf"),
      ];

    let buttonStyle =
      Style.[
        backgroundColor(StyleColors.buttonColor),
        border(~width=1, ~color=Colors.black),
        marginLeft(8),
        marginRight(8),
        paddingLeft(12),
        paddingRight(12),
      ];

    <View style=containerStyle>
      <Row>
        <Text style=countStyle text={string_of_int(count)} />
        <Clickable style=buttonStyle onClick={_ => setCount(n => n + 1)}>
          <Text style=countStyle text="Count" />
        </Clickable>
      </Row>
    </View>;
  };
};

let render = () => <Example />;
