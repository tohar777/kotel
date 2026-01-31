FileManager.init({
    container: '#fileManager',
    options: {
        showThumbnails: true,
        // Customize your FileManager options here
    },
    // Function to get file structure from the server
    getFileStructure: function (path, callback) {
        const apiUrl = '/api/files?path=' + (path || '');

        fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                // Format the file structure to match FileManager's expected structure
                const fileStructure = data.map(item => ({
                    name: item.name,
                    type: item.type,
                    path: item.path,
                }));

                // Callback function to pass data to FileManager
                callback(fileStructure);
            })
            .catch(error => console.error('Error fetching file structure:', error));
    }
});