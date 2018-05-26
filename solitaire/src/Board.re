module Styles = {
  open Css;
  let board = style([
                    backgroundColor(green),
                    display(`flex)
  ]);
}

let component = ReasonReact.statelessComponent("Board");

let make = _children => {
  ...component,
  render: _self =>
    <div className=Styles.board>
      <div>{ReasonReact.string("1")}</div>
      <div>{ReasonReact.string("2")}</div>
      <div>{ReasonReact.string("3")}</div>
      <div>{ReasonReact.string("4")}</div>
    </div>
};
