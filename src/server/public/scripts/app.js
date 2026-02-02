//Pages

//Home
const home = `
        <br>
        <br>
        <br>
        <br>
        <center>
            <h1>Welcome to the Kotel Repository Hosting Server</h1>
            <p>
                This is the default home page 
                if you want to change please go to scripts/app.js and modify it
            </p>
        </center>
`;
//in case of a private server it's recommand to delete the add Repo page
const about = `
        <br>
        <br>
        <br>
        <br>
        <center>
            <h1>About Kotel Repository Server</h1>
            <p>
                Developers:Tohar Zioni
                Server Admin:John Doe
                Server Admin Email:main@example.com    
            </p>
        </center>
`


document.getElementById("content").innerHTML = home;

document.getElementById("home").onclick =function(e){
    document.getElementById("content").innerHTML = home;
};

document.getElementById("about").onclick =function(e){
    document.getElementById("content").innerHTML = about;
};