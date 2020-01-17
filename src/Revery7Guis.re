open Revery;
open Revery.UI;

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

  let _: React.element(React.reveryNode) => unit =
    UI.start(win, <ExampleHost window=win />);
  ();
};

App.start(init);
