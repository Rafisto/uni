import { BaseReliability, EstimatedReliability } from "../model";
import { API_BASE_URL } from "./config";

const fetchSimulation = async () => {
    const response = await fetch(`${API_BASE_URL}/simulation`);
    return response.json();
};

const fetchBaseReliability = async (): Promise<BaseReliability> => {
    const response = await fetch(`${API_BASE_URL}/reliability/base`);
    return response.json();
};

interface EstimatedReliabilityQuery {
    p: number;
    tmax: number;
    iterations: number;
}

const fetchReliability = async (
    q: EstimatedReliabilityQuery
): Promise<EstimatedReliability> => {
    const params = new URLSearchParams({
        p: q.p.toString(),
        tmax: q.tmax.toString(),
        iterations: q.iterations.toString(),
    });

    const response = await fetch(
        `${API_BASE_URL}/reliability/estimate?${params.toString()}`
    );
    return response.json();
};

export { fetchSimulation, fetchBaseReliability, fetchReliability };
export type { EstimatedReliabilityQuery };
