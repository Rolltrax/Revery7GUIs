open Revery;
open Revery.UI;
open Revery.UI.Components;

module Example = {
  let%component make = () => {
    let%hook (degC, setDegC) = Hooks.state(0);
    let%hook (degF, setDegF) = Hooks.state(32);

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

    let labelStyle =
      Style.[
        fontSize(14),
        color(Colors.black),
        fontFamily("Roboto-Regular.ttf"),
      ];

    let inputStyle =
      Style.[
        backgroundColor(StyleColors.buttonColor),
        border(~width=1, ~color=Colors.black),
        marginLeft(8),
        marginRight(8),
        paddingLeft(12),
        paddingRight(12),
        fontSize(12),
        height(22),
      ];

    let setFahrenheitByCelcius = str =>
      switch (int_of_string_opt(str)) {
      | Some(n) =>
        setDegC(_ => n);
        setDegF(_ => n * 9 / 5 + 32);
      | None => ()
      };

    let setCelsiusByFahrenheit = str =>
      switch (int_of_string_opt(str)) {
      | Some(n) =>
        setDegF(_ => n);
        setDegC(_ => (n - 32) * 5 / 9);
      | None => ()
      };

    <View style=containerStyle>
      <View
        style=Style.[
          flexDirection(`Row),
          alignItems(`Center),
          justifyContent(`Center),
        ]>
        <Input
          value={string_of_int(degC)}
          style=inputStyle
          onChange={(value, _) => setFahrenheitByCelcius(value)}
        />
        <Text text="°C" style=labelStyle />
        <Text
          text="="
          style=Style.[
            fontSize(24),
            color(Colors.black),
            marginLeft(8),
            marginRight(8),
            fontFamily("Roboto-Regular.ttf"),
          ]
        />
        <Input
          value={string_of_int(degF)}
          style=inputStyle
          onChange={(value, _) => setCelsiusByFahrenheit(value)}
        />
        <Text text="°F" style=labelStyle />
      </View>
    </View>;
  };
};

let render = () => <Example />;
