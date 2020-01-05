open Revery;
open Revery.UI;
open Revery.UI.Components;

module Example = {
  let%component make = () => {
    let%hook ((degC, degF), setDeg) = Hooks.state(("", ""));
    let setDegC = degC => {
      switch (int_of_string_opt(degC)) {
      | Some(vDegC) =>
        setDeg(_ => (degC, string_of_int(vDegC * 9 / 5 + 32)))
      | None => setDeg(((_, degF)) => (degC, degF))
      };
    };
    let setDegF = degF => {
      switch (int_of_string_opt(degF)) {
      | Some(vDegF) =>
        setDeg(_ => (string_of_int((vDegF - 32) * 5 / 9), degF))
      | None => setDeg(((degC, _)) => (degC, degF))
      };
    };

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

    <View style=containerStyle>
      <View
        style=Style.[
          flexDirection(`Row),
          alignItems(`Center),
          justifyContent(`Center),
        ]>
        <Input
          value=degC
          style=inputStyle
          onChange={(value, _) => setDegC(value)}
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
          value=degF
          style=inputStyle
          onChange={(value, _) => setDegF(value)}
        />
        <Text text="°F" style=labelStyle />
      </View>
    </View>;
  };
};

let render = () => <Example />;
