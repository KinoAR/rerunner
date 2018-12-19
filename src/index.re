open Reprocessing;

/* Environment Variables */
let width = 500;
let height = 500;
let playerSize = (20.0, 30.0);
let playerColor = Utils.color(~r=100, ~g=100, ~b=100, ~a=255);
let obstacleColor = Utils.color(~r=50, ~g=50, ~b=50, ~a=255);
let backgroundColor = Utils.color(~r=200, ~g=200, ~b=200, ~a=255);

type runningT = Alive | Dead | Restart;
type obstacleT = {
  position: (float, float),
  size: (float, float),
};
type stateT = {
  score: int,
  highScore: int,
  playerPosition:(float,float),
  obstacles: list(obstacleT),
  running: runningT
};

let setup = (env) =>{
  Env.size(~width, ~height, env);
  {
    score: 0,
    highScore: 0,
    playerPosition: (30.0, 300.0),
    obstacles: [],
    running: Alive
  };
}

let drawRect = (~pos, ~size, ~color, env) => {
  let (width, height) = size;
  Draw.fill(color, env);
  Draw.rectf(~pos=pos, ~width, ~height, env);
}

let drawCenteredText = (~text, ~y, env) => {
  let width = Draw.textWidth(~body=text, env);
  let center = Env.width(env) / 2 - width;
  Draw.text(~body=text, ~pos=(center, y), env);
};

let movePosition = (~pos, env) => {
  let (x, y) = pos;
  Env.key(Up, env) || Env.key(W, env) ? (x,y +. 10.0) : (x,y);
}

let draw = ({
  score,
  playerPosition,
  highScore,
  obstacles,
  running
} as state, env) => {
  Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
  /* Draw Player & Obstacles & Text*/
  drawRect(~pos=playerPosition, ~size=playerSize, ~color=playerColor, env);
  List.iter((obstacle) => {
    drawRect(~pos=obstacle.position, ~size=obstacle.size, ~color=obstacleColor, env);
  }, obstacles)

  drawCenteredText(~text="Score: " ++ string_of_int(score), ~y=40, env);
  drawCenteredText(~text="High Score: " ++ string_of_int(highScore), ~y=10, env);
  /* Calculate if player hit obstacle */

  let hitObstacle = List.exists((obstacle) => {
    let (playerW, playerH) = playerSize;
    let (obstacleW, obstacleH) = obstacle.size;
    Utils.intersectRectRect(
      ~rect1Pos=playerPosition,
      ~rect1W=playerW,
      ~rect1H=playerH,
      ~rect2Pos=obstacle.position,
      ~rect2W=obstacleW,
      ~rect2H=obstacleH
      )
  }, obstacles);

  switch(running) {
    | Alive => {
      ...state,
      score: score+1,
      playerPosition: movePosition(~pos=playerPosition, env),
      running: hitObstacle ? Dead : Alive
    }
    | Dead => {
        ...state,
        score: score,
        running: Restart
      }
    | Restart => {
      ...state,
      score: 0,
      highScore: score,
      running: Alive,
    }
  };
};

run(~setup, ~draw, ());
