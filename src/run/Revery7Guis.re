open Revery;
open Revery.UI;
open Lib_view;

let load = {
  let filename =
    if (Array.length(Sys.argv) > 1) {
      Sys.argv[1];
    } else if (Sys.file_exists("_build") && Sys.is_directory("_build")) {
      "_build";
    } else {
      Sys.getcwd();
    };
  let filename = Filename.concat(filename, "default");
  let name = Dynlink.adapt_filename("src/lib_view.cma");
  let filename = Filename.concat(filename, name);
  fun
  | () => {
      let () = print_endline("We will build :" ++ filename);
      let start = Unix.gettimeofday();
      let _: int = Sys.command("dune build " ++ name);
      let end_ = Unix.gettimeofday();
      let () = Printf.printf("Builded in %f seconds\n%!", end_ -. start);
      let () = print_endline("We will load :" ++ filename);
      Dynlink.loadfile_private(filename);
      print_endline("We have loaded :" ++ name);
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

  let _: React.element(React.reveryNode) => unit =
    UI.start(win, <ExampleHost window=win />);
  ();
};
if (!Dynlink.is_native) {
  load();
};

let onIdle = () => {
  if (!Dynlink.is_native) {
    load();
  };
  print_endline("Example: idle callback triggered");
};

App.start(~onIdle, init);
