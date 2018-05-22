/* TODO convert if else blocks to variants/matchers if suitable */
/* separate logic into modules */

module Data = {
  let words = [|
    "charming",
    "demonic",
    "dust",
    "clean",
    "halting",
    "penitent",
    "stocking",
    "many",
    "soothe",
    "regret",
    "watch",
    "hissing"
  |];

  let randomElement = (arr: array(string)) => arr[Random.int(Array.length(arr))];
};

module Game = {
  type gameData = {
    matches: list(char),
    fails: list(char),
    word: string
  };

  let concealWord = ({matches, word}: gameData) => {
    let revealMatches = (ch: char) =>
      if (List.mem(ch, matches)) {
        ch;
      } else {
        '_';
      };
    String.map(revealMatches, word);
  };

  let matchLetter = (~letter: string, {matches, fails, word}: gameData) => {
    let ch: char = letter.[0];
    if (List.mem(ch, matches) || List.mem(ch, fails)) {
      print_string("You have already guessed that letter.\n");
      (matches, fails);
    } else if (String.contains(word, ch)) {
      ([ch, ...matches], fails);
    } else {
      (matches, [ch, ...fails]);
    };
  };

  let rec gameLoop = ({matches, fails, word} as game: gameData) => {
    let concealed: string = concealWord(game);
    if (concealed == word) {
      print_string("The word is: " ++ word);
    } else if (List.length(fails) < 4) {
      print_string(concealed);
      print_string("\nGuess a letter: ");
      let letter: string = read_line();
      let (matches, fails) = matchLetter(~letter, game);
      gameLoop({...game, matches, fails});
    } else {
      print_string("You are out of guesses.\n");
    };
  };
};

let () = {
  Random.self_init();
  let word = Data.randomElement(Data.words);
  Game.gameLoop({matches: [], fails: [], word});
};
