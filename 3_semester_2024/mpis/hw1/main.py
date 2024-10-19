import numpy as np
import matplotlib.pyplot as plt
from typing import List, Callable, Tuple


class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Simulation(object):
    def __init__(self, function: Callable, interval: Tuple[int, int], M: float):
        """
        :param function: function to be simulated
        :param interval: range of the function, as a tuple[start, end] # range is reserved in python
        """
        if not callable(function):
            raise TypeError("The function must be callable")
        self.function = function

        if not isinstance(interval, tuple) or len(interval) != 2 or not all(isinstance(i, (int, float)) for i in interval):
            raise TypeError("The range must be a tuple of two integers / floats")
        if interval[0] > interval[1]:
            raise ValueError(
                "The range start must be lower than the range end")

        self.interval = interval

        self.M = M

    def generate_points(self, n: int) -> List[Point]:
        """
        :param n: number of points to be generated
        :return: a list of n points, with x in the range and y in [0, M]
        """
        points = []
        # MT19937 is the Mersenne Twister PRNG, see https://numpy.org/doc/stable/reference/random/bit_generators/mt19937.html
        rng = np.random.Generator(np.random.MT19937())
        for _ in range(n):
            x = rng.uniform(self.interval[0], self.interval[1])
            y = rng.uniform(0, self.M)
            points.append(Point(x, y))
        return points

    def is_under_the_curve(self, point: tuple[int, int]):
        """
        :param x: x coordinate
        :param y: y coordinate
        :return: evaluation of the inequality y <= f(x), at the given point
        """
        return point.y <= self.function(point.x)

    def count_under_curve(self, points: List[Point]) -> int:
        """
        :param points: a list of points
        :return: the number of points that are under the curve
        """
        return sum([self.is_under_the_curve(point) for point in points])

    def calculate_approximated_area(self, n: int) -> float:
        """
        :param n: number of points to be generated
        :return: the approximated area under the curve
        """
        points = self.generate_points(n)
        under_curve = self.count_under_curve(points)
        return under_curve / n * (self.interval[1] - self.interval[0]) * self.M


class Graph():
    @staticmethod
    def CreateGraph(points: List[Point], means: List[Point], true_value: float, title: str, subtitle: str, filename: str = None):
        """
        :param points: a list of points
        :param means: a list of points, where each point is the mean of the points up to that index
        :param true_value: the true value of the integral
        """
        plt.clf()

        plt.grid(True)

        x = [point.x for point in points]
        y = [point.y for point in points]
        plt.scatter(x, y, label="Approximated area", color="blue", s=2)

        x = [point.x for point in means]
        y = [point.y for point in means]
        plt.scatter(x, y, label="Mean approximated area", color="red", s=8)

        plt.axhline(y=true_value, color='lime',
                    linestyle='-', label="True value", lw=2)

        plt.title(title, fontsize=12)
        plt.suptitle(subtitle, y=0.05, fontsize=10)

        plt.legend()

        if filename:
            plt.savefig(filename)


class TestFunctions():
    @staticmethod
    def f1(x: float) -> float:
        """
        :param x: a float
        :return: f1(x) = x^{1/3}
        """
        return x**(1/3)

    @staticmethod
    def f2(x: float) -> float:
        """
        :param x: a float
        :return: f2(x) = sin(x)
        """
        return np.sin(x)

    @staticmethod
    def f3(x: float) -> float:
        """
        :param x: an float
        :return: f3(x) = 4x(1-x)^3
        """
        return 4*x*(1-x)**3


def run_simulation(test_function, function_name, interval, limsup, n_range, K, true_value, graph_title, graph_subtitle, filename_template):
    sim = Simulation(test_function, interval, limsup)
    points = []
    means = []

    Nmin, Nmax, Nstep = n_range
    for n in range(Nmin, Nmax + Nstep, Nstep):
        print(f"Simulating {function_name} with n={
              n}, progress: {n/Nmax*100:.2f}%")
        current_points = []
        for k in range(K):
            area = sim.calculate_approximated_area(n)
            current_points.append(Point(n, area))
        means.append(Point(n, np.mean([point.y for point in current_points])))
        points.extend(current_points)

    Graph.CreateGraph(
        points=points,
        means=means,
        true_value=true_value,
        title=graph_title,
        subtitle=graph_subtitle,
        filename=filename_template.format(K=K)
    )


if __name__ == "__main__":
    # Sim 1
    Nmin, Nmax, Nstep = 50, 5000, 50
    true_value = 12  # wolframalpha: integrate from 0 to 8 x^(1/3) dx
    limsup = 2 # limsup of f1(x) = x^(1/3) in [0, 8]

    # Sim 1 K=5
    run_simulation(
        test_function=TestFunctions.f1,
        function_name="f1(x) = x^(1/3)",
        interval=(0, 8),
        limsup=limsup,
        n_range=(Nmin, Nmax, Nstep),
        K=5,
        true_value=true_value,
        graph_title="Simulation of $f_1(x) = \\sqrt[3]{x}$",
        graph_subtitle="Nmin=50, Nmax=5000, Nstep=50, K=5",
        filename_template="f1=cuberoot_x_and_k={K}.png"
    )

    # Sim 1 K=50
    run_simulation(
        test_function=TestFunctions.f1,
        function_name="f1(x) = x^(1/3)",
        interval=(0, 8),
        limsup=limsup,
        n_range=(Nmin, Nmax, Nstep),
        K=50,
        true_value=true_value,
        graph_title="Simulation of $f_1(x) = \\sqrt[3]{x}$",
        graph_subtitle="Nmin=50, Nmax=5000, Nstep=50, K=50",
        filename_template="f1=cuberoot_x_and_k={K}.png"
    )

    # Sim 2
    true_value = 2  # wolframalpha: integrate from 0 to pi sin(x) dx
    limsup = 1 # limsup of f2(x) = sin(x) in [0, pi]

    # Sim 2 K=5
    run_simulation(
        test_function=TestFunctions.f2,
        function_name="f2(x) = sin(x)",
        interval=(0, np.pi),
        limsup=limsup,
        n_range=(Nmin, Nmax, Nstep),
        K=5,
        true_value=true_value,
        graph_title="Simulation of $f_2(x) = sin(x)$",
        graph_subtitle="Nmin=50, Nmax=5000, Nstep=50, K=5",
        filename_template="f2=sin_x_and_k={K}.png"
    )

    # Sim 2 K=50
    run_simulation(
        test_function=TestFunctions.f2,
        function_name="f2(x) = sin(x)",
        interval=(0, np.pi),
        limsup=limsup,
        n_range=(Nmin, Nmax, Nstep),
        K=50,
        true_value=true_value,
        graph_title="Simulation of $f_2(x) = sin(x)$",
        graph_subtitle="Nmin=50, Nmax=5000, Nstep=50, K=50",
        filename_template="f2=sin_x_and_k={K}.png"
    )

    # Sim 3
    true_value = 0.2  # wolframalpha: integrate from 0 to 1 4x(1-x)^3 dx
    limsup = 0.421875 # limsup of f3(x) = 4x(1-x)^3 in [0, 1]

    # Sim 3 K=5
    run_simulation(
        test_function=TestFunctions.f3,
        function_name="f3(x) = 4x(1-x)^3",
        interval=(0, 1),
        limsup=limsup,
        n_range=(Nmin, Nmax, Nstep),
        K=5,
        true_value=true_value,
        graph_title="Simulation of $f_3(x) = 4x(1-x)^3$",
        graph_subtitle="Nmin=50, Nmax=5000, Nstep=50, K=5",
        filename_template="f3=4x1-x3_x_and_k={K}.png"
    )

    # Sim 3 K=50
    run_simulation(
        test_function=TestFunctions.f3,
        function_name="f3(x) = 4x(1-x)^3",
        interval=(0, 1),
        limsup=limsup,
        n_range=(Nmin, Nmax, Nstep),
        K=50,
        true_value=true_value,
        graph_title="Simulation of $f_3(x) = 4x(1-x)^3$",
        graph_subtitle="Nmin=50, Nmax=5000, Nstep=50, K=50",
        filename_template="f3=4x1-x3_x_and_k={K}.png"
    )
