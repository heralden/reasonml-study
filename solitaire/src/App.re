module Styles = {
  open Css;
  let logo = {
    let spin =
      Css.keyframes([
        (0, [transform(rotate(deg(0)))]),
        (100, [transform(rotate(deg(360)))]),
      ]);
    style([
      animationName(spin),
      animationDuration(20000),
      animationTimingFunction(linear),
      animationIterationCount(infinite),
      height(px(80)),
    ]);
  };
  let app = style([textAlign(center)]);
  let header = style([
                     background(hex("222")),
                     height(px(150)),
                     padding(px(20)),
                     color(white),
  ]);
  let intro = style([
                    unsafe("fontSize", "large"),
  ]);
};

[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.app>
      <div className=Styles.header>
        <img src=logo className=Styles.logo alt="logo" />
        <h2> (ReasonReact.string(message)) </h2>
      </div>
      <p className=Styles.intro>
        (ReasonReact.string("To get started, edit"))
        <code> (ReasonReact.string(" src/App.re ")) </code>
        (ReasonReact.string("and save to reload."))
      </p>
    </div>,
};
