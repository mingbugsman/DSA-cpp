const graph = {
    'A': [{ node: 'B', weight: 4 }, { node: 'C', weight: 2 }],
    'B': [{ node: 'C', weight: 5 }, { node: 'D', weight: 10 }],
    'C': [{ node: 'B', weight: 3 }, { node: 'D', weight: 8 }, { node: 'E', weight: 10 }],
    'D': [{ node: 'E', weight: 2 }],
    'E': [{ node: 'D', weight: 6 }]
};

const cy = cytoscape({
    container: document.getElementById('cy'),
    elements: [
      
    ],
    style: [
        {
            selector: 'node',
            style: {
                'label': node => node.data('id') + (node.data('distance') !== undefined ? ': ' + node.data('distance') : ''),
                'background-color': 'gray',
                'text-valign': 'center',
                'color': 'white'
            }
        },
        {
            selector: 'edge',
            style: {
                'label': 'data(weight)',
                'text-outline-color': '#fff',
                'text-outline-width': 2,
                'curve-style': 'bezier',
                'width': 2
            }
        }
    ],
    layout: { name: 'grid' }
});


// Reset Button
document.getElementById('reset-btn').addEventListener('click', function() {
    cy.elements().remove();
    cy.layout({ name: 'grid' }).run();
});

document.getElementById('reset-algorithm').addEventListener('click', function() {
    cy.nodes().style('background-color', '#ddd'); 
    document.getElementById('dfs-output').innerHTML = ""; // Xóa danh sách DFS
});


// Add Node
document.getElementById('add-node-btn').addEventListener('click', function() {
    var nodeId = document.getElementById('node-input').value;
    if (nodeId && !cy.getElementById(nodeId).length) {
        cy.add({ data: { id: nodeId } });
        cy.layout({ name: 'grid' }).run();
        document.getElementById('node-input').value = '';
    }
});


document.getElementById('add-edge-btn').addEventListener('click', function() {
    var source = document.getElementById('source-input').value;
    var target = document.getElementById('target-input').value;
    var weight = parseInt(document.getElementById('weight-input').value);

    // Kiểm tra dữ liệu hợp lệ
    if (source && target && !isNaN(weight) && 
        cy.getElementById(source).length && cy.getElementById(target).length) {
        cy.add({
            data: { source: source, target: target, weight: weight }
        });
        cy.layout({ name: 'grid' }).run(); // Cập nhật bố cục đồ thị
        // Xóa nội dung input
        document.getElementById('source-input').value = '';
        document.getElementById('target-input').value = '';
        document.getElementById('weight-input').value = '';
    } else {
        alert("Vui lòng nhập đầy đủ và chính xác thông tin!");
    }
});