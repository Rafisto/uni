const MIN_NODE_DISPLAY_SIZE = 20;
const MAX_NODE_DISPLAY_SIZE = 50;

const nodeLoadToSize = (load: number[]) => {
  let min = Math.min(...load);
  let max = Math.max(...load);
  return load.map(
    (x) =>
      ((x - min) / (max - min)) *
        (MAX_NODE_DISPLAY_SIZE - MIN_NODE_DISPLAY_SIZE) +
      MIN_NODE_DISPLAY_SIZE
  );
};

const MIN_NODE_BLUE = 64;
const MAX_NODE_BLUE = 255;

const nodeLoadToColor = (load: number[]) => {
  let min = Math.min(...load);
  let max = Math.max(...load);
  return load.map(
    (x) =>
      `rgb(0,0, ${Math.round(
        ((x - min) / (max - min)) * (MAX_NODE_BLUE - MIN_NODE_BLUE) +
          MIN_NODE_BLUE
      )})`
  );
};

const MIN_LOAD = 0;
const MAX_LOAD = 100;

const MIN_WIDTH = 0;
const MAX_WIDTH = 2;

const linkLoadToWidth = (load: number) => {
  return (
    MIN_WIDTH +
    (MAX_WIDTH - MIN_WIDTH) *
      Math.pow((load - MIN_LOAD) / (MAX_LOAD - MIN_LOAD), 1/5)
  );
};

const MIN_LINK_LOAD = 0;
const MAX_LINK_LOAD = 1000;

const linkLoadToColor = (load: number) => {
  let color = Math.round(((load - MIN_LINK_LOAD) / (MAX_LINK_LOAD - MIN_LINK_LOAD)) * 255);

  return `rgb(${color}, ${color}, ${color})`;
};

export { nodeLoadToSize, nodeLoadToColor, linkLoadToWidth, linkLoadToColor };
