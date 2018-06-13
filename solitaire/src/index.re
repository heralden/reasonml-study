Css.(
  global(
    "body",
    [margin(px(0)), padding(px(0)), fontFamily("sans-serif"), backgroundColor(green)],
  )
);

ReactDOMRe.renderToElementWithId(
  <App message="Welcome to React and Reason" />,
  "root",
);
