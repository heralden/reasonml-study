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
  piles: array(pile),
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
    ArrayLabels.fold_left(
      ~f=
        (acc, amount) => {
          let (deck, piles) = acc;
          let (hand, deck) = Game.pickHand(~amount, deck);
          (deck, ArrayLabels.append(piles, [|hand|]));
        },
      ~init=(Game.createDeck(), [||]),
      [|1, 2, 3, 4, 5, 6, 7|],
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

let topCard = (cards: list(Game.card)) =>
  switch (cards) {
  | [card, ..._] => <Card card />
  | [] => <div />
  };

let make = _children => {
  ...component,
  initialState: createBoard,
  reducer: (action, state: state) =>
    switch (action) {
    | Draw => ReasonReact.Update(state)
    | Move => ReasonReact.Update(state)
    | Save => ReasonReact.Update(state)
    },
  render: self =>
    <div>
      <div className=Styles.board>
        <div className=Styles.stock>
          <div className=Styles.pile>
            {ReasonReact.string("Deck")}
            {topCard(self.state.stock)}
          </div>
          <div className=Styles.pile>
            {ReasonReact.string("Hand")}
            {topCard(self.state.hand)}
          </div>
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("Diamonds")}
          {topCard(self.state.foundation.diamonds)}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("Clubs")}
          {topCard(self.state.foundation.clubs)}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("Hearts")}
          {topCard(self.state.foundation.hearts)}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("Spades")}
          {topCard(self.state.foundation.spades)}
        </div>
      </div>
      <div className=Styles.board>
        <div className=Styles.pile>
          {ReasonReact.string("1")}
          {topCard(self.state.piles[0])}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("2")}
          {topCard(self.state.piles[1])}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("3")}
          {topCard(self.state.piles[2])}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("4")}
          {topCard(self.state.piles[3])}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("5")}
          {topCard(self.state.piles[4])}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("6")}
          {topCard(self.state.piles[5])}
        </div>
        <div className=Styles.pile>
          {ReasonReact.string("7")}
          {topCard(self.state.piles[6])}
        </div>
      </div>
    </div>,
};
