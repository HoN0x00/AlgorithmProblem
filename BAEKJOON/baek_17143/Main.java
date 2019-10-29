package baek_17143;

import java.util.Scanner;

public class Main {
	static int[] dirx = { 0, -1, 1, 0, 0 };
	static int[] diry = { 0, 0, 0, 1, -1 };
	static int r;
	static int c;
	static int m;
	static int maxSpeedr;
	static int maxSpeedc;

	static class Pos {
		int x;
		int y;
		int dir;

		Pos(int x, int y, int dir) {
			this.x = x;
			this.y = y;
			this.dir = dir;
		}
	}

	static class SharkInfo {
		int speed;
		int direction;
		int size;
		boolean isExist;

		SharkInfo() {
			this.speed = 0;
			this.direction = 0;
			this.size = 0;
			isExist = false;
		}

		void setShark(int speed, int direction, int size) {
			this.speed = speed;
			this.direction = direction;
			this.size = size;

			isExist = true;
		}
	}

	public static Pos calcMove(Pos start, int speed) {
		Pos end = new Pos(start.x, start.y, start.dir);

		for (int i = 0; i < speed; i++) {
			int nx = end.x + dirx[end.dir];
			int ny = end.y + diry[end.dir];

			if (nx <= 0 || ny <= 0 || nx > r || ny > c) {
				if (end.dir == 1 || end.dir == 3) {
					end.dir += 1;
				} else {
					end.dir -= 1;
				}

				end.x += dirx[end.dir];
				end.y += diry[end.dir];
			} else {
				end.x = nx;
				end.y = ny;
			}
		}

		return end;
	}

	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);

		r = sc.nextInt();
		c = sc.nextInt();
		m = sc.nextInt();

		maxSpeedr = 2 * (r - 1);
		maxSpeedc = 2 * (c - 1);

		SharkInfo[][][] map = new SharkInfo[2][r + 1][c + 1];

		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				map[0][i][j] = new SharkInfo();
				map[1][i][j] = new SharkInfo();
			}
		}

		int turn = 0;

		for (int i = 0; i < m; i++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			int speed = sc.nextInt();
			int direction = sc.nextInt();
			int size = sc.nextInt();

			if (direction == 1 || direction == 2)
				speed = speed % maxSpeedr;
			else
				speed = speed % maxSpeedc;

			map[turn][x][y].setShark(speed, direction, size);
		}

		int answer = 0;

		for (int p = 1; p <= c; p++) {
			for (int h = 1; h <= r; h++) {
				if (map[turn][h][p].isExist) {
					answer += map[turn][h][p].size;

					map[turn][h][p].isExist = false;
					break;
				}
			}

			int nextTurn = (turn + 1) % 2;

			for (int i = 1; i <= r; i++) {
				for (int j = 1; j <= c; j++) {
					if (map[turn][i][j].isExist) {
						Pos cur = new Pos(i, j, map[turn][i][j].direction);
						Pos next = calcMove(cur, map[turn][i][j].speed);

						if (map[nextTurn][next.x][next.y].isExist) {
							if (map[nextTurn][next.x][next.y].size < map[turn][i][j].size) {

								map[nextTurn][next.x][next.y].setShark(map[turn][i][j].speed, next.dir,
										map[turn][i][j].size);
							}
						} else {
							map[nextTurn][next.x][next.y].setShark(map[turn][i][j].speed, next.dir,
									map[turn][i][j].size);
						}

						map[turn][i][j].isExist = false;
					}
				}
			}

			turn = (turn + 1) % 2;
		}

		System.out.println(answer);

		sc.close();
	}
}
