module Styles = {
  open Css;
  let board =
    style([
      padding(px(10)),
      display(`flex),
      flexWrap(`nowrap),
      justifyContent(`center),
    ]);
  let pile =
    style([
      width(px(127)),
      height(px(177)),
      marginRight(px(15)),
      border(px(1), `solid, black),
      borderRadius(px(5)),
    ]);
  let stock =
    style([display(`flex), flexWrap(`nowrap), marginRight(`auto)]);
};

type pile = list(Game.card);
type foundation = {
  diamonds: list(Game.card),
  clubs: list(Game.card),
  hearts: list(Game.card),
  spades: list(Game.card),
};

type state = {
  stock: list(Game.card),
  hand: list(Game.card),
  foundation,
  piles: list(pile),
};

/* Draw: a hand */
/* Move: one or more cards around */
/* Save: a card to the foundation */
type action =
  | Draw
  | Move
  | Save;

let createBoard = () => {
  let (stock, piles) =
    ListLabels.fold_left(
      ~f=
        (acc, amount) => {
          let (deck, piles) = acc;
          let (hand, deck) = Game.pickHand(~amount, deck);
          (deck, ListLabels.append(piles, [hand]));
        },
      ~init=(Game.createDeck(), []),
      [1, 2, 3, 4, 5, 6, 7],
    );

  {
    stock,
    piles,
    hand: [],
    foundation: {
      diamonds: [],
      clubs: [],
      hearts: [],
      spades: [],
    },
  };
};

let component = ReasonReact.reducerComponent("Board");

let make = _children => {
  ...component,
  initialState: createBoard,
  reducer: (action, state: state) =>
    switch (action) {
    | Draw => ReasonReact.Update(state)
    | Move => ReasonReact.Update(state)
    | Save => ReasonReact.Update(state)
    },
  render: _self =>
    <div>
      <div className=Styles.board>
        <div className=Styles.stock>
          <div className=Styles.pile> (ReasonReact.string("Deck")) </div>
          <div className=Styles.pile> (ReasonReact.string("Hand")) </div>
        </div>
        <div className=Styles.pile> (ReasonReact.string("Diamonds")) </div>
        <div className=Styles.pile> (ReasonReact.string("Clubs")) </div>
        <div className=Styles.pile> (ReasonReact.string("Hearts")) </div>
        <div className=Styles.pile> (ReasonReact.string("Spades")) </div>
      </div>
      <div className=Styles.board>
        <div className=Styles.pile> (ReasonReact.string("1")) </div>
        <div className=Styles.pile> (ReasonReact.string("2")) </div>
        <div className=Styles.pile> (ReasonReact.string("3")) </div>
        <div className=Styles.pile> (ReasonReact.string("4")) </div>
        <div className=Styles.pile> (ReasonReact.string("5")) </div>
        <div className=Styles.pile> (ReasonReact.string("6")) </div>
        <div className=Styles.pile> (ReasonReact.string("7")) </div>
      </div>
    </div>,
};
