type suite = Clubs | Diamonds | Hearts | Spades;
let suites = [ Clubs, Diamonds, Hearts, Spades ];
type rank = King | Queen | Jack | Number(int) | Ace;
let ranks = [ King, Queen, Jack, Number(10), Number(9), Number(8), Number(7), Number(6), Number(5), Number(4), Number(3), Number(2), Ace ];
type card = (suite, rank);

let myCard: card = ( Clubs, King );

let createDeck = (): list(card) => {

  let createRanks = () => {};

  let createSuits = (deck: list(card), suite: suite) => {
    ListLabels.fold_left(~f=createRanks(suite), ~init=deck, ranks);
  };

  ListLabels.fold_left(~f=createSuits, ~init=[], suites);
};
