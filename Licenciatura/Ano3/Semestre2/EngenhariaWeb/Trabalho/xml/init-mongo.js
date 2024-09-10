const { exec } = require('child_process');

exec('mongoimport --db ruas --collection ruas --file /docker-entrypoint-initdb.d/output.json --jsonArray', (err, stdout, stderr) => {
    if (err) {
        console.error(`Error importing data: ${stderr}`);
        process.exit(1);
    } else {
        console.log(`Data imported: ${stdout}`);
    }
});