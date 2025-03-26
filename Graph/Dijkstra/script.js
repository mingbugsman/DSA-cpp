class MinHeap {
    constructor() {
        this.heap = [];
    }

    enqueue(node, priority) {
        this.heap.push({ node, priority });
        this.bubbleUp(this.heap.length - 1);
    }

    dequeue() {
        if (this.heap.length === 0) return null;
        if (this.heap.length === 1) return this.heap.pop().node;

        const min = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.bubbleDown(0);
        return min.node;
    }

    bubbleUp(index) {
        while (index > 0) {
            const parent = Math.floor((index - 1) / 2);
            if (this.heap[parent].priority <= this.heap[index].priority) break;
            [this.heap[parent], this.heap[index]] = [this.heap[index], this.heap[parent]];
            index = parent;
        }
    }

    bubbleDown(index) {
        const length = this.heap.length;
        while (true) {
            let smallest = index;
            const left = 2 * index + 1;
            const right = 2 * index + 2;

            if (left < length && this.heap[left].priority < this.heap[smallest].priority) {
                smallest = left;
            }
            if (right < length && this.heap[right].priority < this.heap[smallest].priority) {
                smallest = right;
            }
            if (smallest === index) break;

            [this.heap[index], this.heap[smallest]] = [this.heap[smallest], this.heap[index]];
            index = smallest;
        }
    }

    isEmpty() {
        return this.heap.length === 0;
    }
}



const gridSize = [25,50]; // Lưới 10x10
const grid = [];
const container = document.getElementById('grid-container');
const annouce = document.getElementById("announce");
const arrows = document.querySelectorAll(".arrow")

// Tạo lưới ô
for (let i = 0; i < gridSize[0]; i++) {
    grid[i] = [];
    for (let j = 0; j < gridSize[1]; j++) {
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
    for (let i = 0; i < gridSize[0]; i++) {
        for (let j = 0; j < gridSize[1]; j++) {
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

    annouce.textContent = "Thông báo thuật toán sẽ xuất hiện tại đây"
    annouce.classList.remove("blinking-border");
    arrows.forEach(arrow => arrow.style.display ="none");
}

function getNeighbors(grid, node) {
    const neighbors = [];
    const directions = [
        [-1, 0], [1, 0], [0, -1], [0, 1] // Lên, Xuống, Trái, Phải
    ];
    
    for (let [dx, dy] of directions) {
        const newX = node.x + dx;
        const newY = node.y + dy;
        if (newX >= 0 && newX < gridSize[0] && newY >= 0 && newY < gridSize[1] && !grid[newX][newY].isObstacle) {
            neighbors.push(grid[newX][newY]);
        }
    }
    return neighbors;
}

function findStartEnd(grid) {
    let start = null, end = null;
    for (let i = 0; i < gridSize[0]; i++) {
        for (let j = 0; j < gridSize[1]; j++) {
            if (grid[i][j].isStart) start = grid[i][j];
            if (grid[i][j].isEnd) end = grid[i][j];
        }
    }
    return { start, end };
}
async function dijkstraVisualization(grid) {
    const { start, end } = findStartEnd(grid);
    if (!start || !end) {
        
        return [];
    }

    start.distance = 0;
    const pq = new MinHeap();
    pq.enqueue(start, 0);
    const visited = new Set();
    const scannedNodes = [];

    while (!pq.isEmpty()) {
        const current = pq.dequeue();
        const key = `${current.x},${current.y}`;
        if (visited.has(key)) continue;
        visited.add(key);

        if (current === end) break;

        if (!current.isStart && !current.isEnd) {
            scannedNodes.push(current);
        }

        const neighbors = getNeighbors(grid, current);
        for (const neighbor of neighbors) {
            const neighborKey = `${neighbor.x},${neighbor.y}`;
            if (visited.has(neighborKey)) continue;

            const newDistance = current.distance + 1; // Trọng số đồng đều
            if (newDistance < neighbor.distance) {
                neighbor.distance = newDistance;
                neighbor.previous = current;
                pq.enqueue(neighbor, newDistance);
            }
        }
    }

    await visualizeScanning(scannedNodes);

    if (end.distance === Infinity) {
        annouce.textContent = "Không tìm thấy đường đi";
        annouce.classList.add("blinking-border");  
        arrows.forEach(arrow => arrow.style.display ="block");
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
        await new Promise(resolve => setTimeout(resolve, 10)); // Delay mỗi ô 50ms
    }
}

// Chạy thuật toán và hiển thị
async function runDijkstra() {
    const path = await dijkstraVisualization(grid);
    await visualizePath(path);
}

// Hiển thị animation đường đi
async function visualizePath(path) {
    if (path.length === 0) {
        annouce.textContent = "Không tìm thấy đường đi";
        annouce.classList.add("blinking-border");
        arrows.forEach(arrow => arrow.style.display ="block");
        return;
    }


    annouce.textContent = "thấy đường đi";
    annouce.classList.add("blinking-border");
    arrows.forEach(arrow => arrow.style.display ="block");
    for (let cell of path) {
        const element = document.querySelector(`[data-x="${cell.x}"][data-y="${cell.y}"]`);
        // Xóa class 'scanned' để màu đường đi đè lên
        element.classList.remove('scanned');
        if (!element.classList.contains('start') && !element.classList.contains('end')) {
            element.classList.add('path');
        }
        await new Promise(resolve => setTimeout(resolve, 70)); // Delay 50ms cho mỗi ô
    }
}




// // Hàm thêm vật cản ngẫu nhiên với xác suất cho mỗi ô
function addRandomObstacles(probability = 0.3) {
    for (let i = 0; i < gridSize[0]; i++) {
        for (let j = 0; j < gridSize[1]; j++) {
            // Nếu ô đã được đặt làm điểm bắt đầu hoặc kết thúc thì bỏ qua
            if (grid[i][j].isStart || grid[i][j].isEnd) continue;
            // Với xác suất probability, đánh dấu ô là vật cản
            if (Math.random() < probability) {
                grid[i][j].isObstacle = true;
                const cell = document.querySelector(`[data-x="${i}"][data-y="${j}"]`);
                cell.classList.add('obstacle');
            }
        }
    }
}

// Ví dụ: Thêm sự kiện cho nút "Random Obstacles" (thêm nút này vào HTML của bạn)
document.getElementById('random-obstacles').addEventListener('click', () => {
    addRandomObstacles(0.3);
});
