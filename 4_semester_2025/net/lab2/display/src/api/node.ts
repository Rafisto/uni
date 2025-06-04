import { API_BASE_URL } from "./config";

const fetchNode = async (node_id: number) => {
  const response = await fetch(`${API_BASE_URL}/nodes/${node_id}`);
  return response.json();
};

const fetchLink = async (link_id: [number, number]) => {
  const response = await fetch(
    `${API_BASE_URL}/links/${link_id[0]}/${link_id[1]}`
  );
  return response.json();
}

export { fetchNode, fetchLink };