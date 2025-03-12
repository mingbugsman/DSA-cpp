class PriorityQueue {
    constructor() {
        this.queue = [];
    }

    enqueue(node, priority) {
        this.queue.push({ node, priority });
        this.queue.sort((a, b) => a.priority - b.priority);
    }

    dequeue() {
        return this.queue.shift().node;
    }

    isEmpty() {
        return this.queue.length === 0;
    }
}



const gridSize = 10; // Lưới 10x10
const grid = [];
const container = document.getElementById('grid-container');

// Tạo lưới ô
for (let i = 0; i < gridSize; i++) {
    grid[i] = [];
    for (let j = 0; j < gridSize; j++) {
        grid[i][j] = {
            x: i,
            y: j,
            isObstacle: false,
            isStart: false,
            isEnd: false,
            distance: Infinity,
            previous: null
        };
        
        // Tạo ô trên giao diện
        const cell = document.createElement('div');
        cell.classList.add('grid-cell');
        cell.dataset.x = i;
        cell.dataset.y = j;
        container.appendChild(cell);
    }
    container.appendChild(document.createElement('br')); // Xuống dòng sau mỗi hàng
}

let settingStart = true;
let settingEnd = false;

container.addEventListener('click', function(event) {
    const cell = event.target;
    if (!cell.classList.contains('grid-cell')) return;

    const x = parseInt(cell.dataset.x);
    const y = parseInt(cell.dataset.y);

    if (settingStart) {
        grid[x][y].isStart = true;
        cell.classList.add('start');
        settingStart = false;
        settingEnd = true;
    } else if (settingEnd) {
        grid[x][y].isEnd = true;
        cell.classList.add('end');
        settingEnd = false;
    } else {
        grid[x][y].isObstacle = !grid[x][y].isObstacle;
        cell.classList.toggle('obstacle');
    }
});
function resetGrid() {
    for (let i = 0; i < gridSize; i++) {
        for (let j = 0; j < gridSize; j++) {
            grid[i][j].isObstacle = false;
            grid[i][j].isStart = false;
            grid[i][j].isEnd = false;
            grid[i][j].distance = Infinity;
            grid[i][j].previous = null;
            const cell = document.querySelector(`[data-x="${i}"][data-y="${j}"]`);
            cell.className = 'grid-cell';
        }
    }
    settingStart = true;
    settingEnd = false;
}

function getNeighbors(grid, node) {
    const neighbors = [];
    const directions = [
        [-1, 0], [1, 0], [0, -1], [0, 1], // Lên, Xuống, Trái, Phải
        [-1, -1], [-1, 1], [1, -1], [1, 1] // Chéo trái trên, chéo phải trên, chéo trái dưới, chéo phải dưới
    ];
    
    for (let [dx, dy] of directions) {
        const newX = node.x + dx;
        const newY = node.y + dy;
        if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridSize && !grid[newX][newY].isObstacle) {
            neighbors.push(grid[newX][newY]);
        }
    }
    return neighbors;
}

function findStartEnd(grid) {
    let start = null, end = null;
    for (let i = 0; i < gridSize; i++) {
        for (let j = 0; j < gridSize; j++) {
            if (grid[i][j].isStart) start = grid[i][j];
            if (grid[i][j].isEnd) end = grid[i][j];
        }
    }
    return { start, end };
}
async function dijkstraVisualization(grid) {
    const { start, end } = findStartEnd(grid);
    if (!start || !end) {
        alert("Vui lòng chọn điểm bắt đầu và kết thúc trước khi chạy thuật toán!");
        return [];
    }

    start.distance = 0;
    const pq = new PriorityQueue();
    pq.enqueue(start, 0);
    const visited = new Set();
    const scannedNodes = [];

    while (!pq.isEmpty()) {
        const current = pq.dequeue();
        if (visited.has(`${current.x},${current.y}`)) continue;
        visited.add(`${current.x},${current.y}`);

        if (current === end) break;

        if (!current.isStart && !current.isEnd) {
            scannedNodes.push(current);
        }

        const neighbors = getNeighbors(grid, current);
        for (const neighbor of neighbors) {
            if (visited.has(`${neighbor.x},${neighbor.y}`)) continue;

            const newDistance = current.distance + 1;
            if (newDistance < neighbor.distance) {
                neighbor.distance = newDistance;
                neighbor.previous = current;
                pq.enqueue(neighbor, newDistance);
            }
        }
    }

    await visualizeScanning(scannedNodes);

    if (end.distance === Infinity) {
        alert("Không tìm thấy đường đi!");
        return [];
    }

    const path = [];
    let current = end;
    while (current) {
        path.unshift(current);
        current = current.previous;
    }

    return path;
}


// Hiển thị animation quét ma trận
async function visualizeScanning(nodes) {
    for (let node of nodes) {
        const element = document.querySelector(`[data-x="${node.x}"][data-y="${node.y}"]`);
        if (!element.classList.contains('start') && !element.classList.contains('end')) {
            element.classList.add('scanned'); // Thêm class để đổi màu
        }
        await new Promise(resolve => setTimeout(resolve, 50)); // Delay mỗi ô 50ms
    }
}

// Chạy thuật toán và hiển thị
async function runDijkstra() {
    const path = await dijkstraVisualization(grid);
    
    document.querySelectorAll('.scanned').forEach(cell => {
        cell.classList.remove('scanned');
    });

    await visualizePath(path);
}

// Hiển thị animation đường đi
async function visualizePath(path) {
    if (path.length === 0) {
        alert("Không tìm được đường đi!");
        return;
    }

    for (let cell of path) {
        const element = document.querySelector(`[data-x="${cell.x}"][data-y="${cell.y}"]`);
        if (!element.classList.contains('start') && !element.classList.contains('end')) {
            element.classList.add('path');
        }
        await new Promise(resolve => setTimeout(resolve, 100)); // Delay mỗi ô 100ms
    }
}
