type suite = Clubs | Diamonds | Hearts | Spades;
let suites = [ Clubs, Diamonds, Hearts, Spades ];
type rank = King | Queen | Jack | Number(int) | Ace;
let ranks = [ King, Queen, Jack, Number(10), Number(9), Number(8), Number(7), Number(6), Number(5), Number(4), Number(3), Number(2), Ace ];
type card = (suite, rank);

Random.self_init();

let shuffleDeck = (deck: list(card)): list(card) => {
  let randomSort = (_c1: card, _c2: card) => Random.int(2);

  ListLabels.fast_sort(~cmp=randomSort, deck);
};

let createDeck = (): list(card) => {

  let consCard = (suite: suite, deck: list(card), rank: rank) =>
    [ (suite, rank), ...deck ];

  let reduceSuits = (deck: list(card), suite: suite) =>
    ListLabels.fold_left(~f=consCard(suite), ~init=deck, ranks);

  let deck = ListLabels.fold_left(~f=reduceSuits, ~init=[], suites);
  shuffleDeck(deck);
};

let pickCard = (deck: list(card)): (card, list(card)) =>
  (ListLabels.hd(deck), ListLabels.tl(deck));

let rec pickHand = (~amount: int=1, ~hand: list(card)=[], deck: list(card)) => {
  if (amount > 0) {
    let (pick, deck) = pickCard(deck);
    let hand = [ pick, ...hand ];
    pickHand(~amount=amount - 1, ~hand, deck);
  } else {
    (hand, deck);
  };
};
