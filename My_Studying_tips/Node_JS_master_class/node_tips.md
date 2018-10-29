# Node tips
* The package.json file
    * Dependency management
    * After using `$ npm install`, it will install all of dependencies in your package.json and store them in a directory called 'node_module', this directory makes you import the package without specify your relative or absolute path of the package, instead just use like `var foo = require('foo')`
    * The information(version, resolved, integrity) of the package which install from the dependencies in package.json will be declared in your package-lock.json file
    * .npmrc, this file contain the key or authentication that can let you access the private(your own) package, and download it automatically. The format of .npmrc will be like `registry.npmjs.org/:_authToken=xxxxx-xxxxx-xxxx-xxxxxxxxxxxxx`
* Test and Task Running
    * Testing script are commonly held in a /test directory, and are triggered by a "test runner" such as Mocha or chai
    * Common testing files included: .travis.yml .jshintrc
    * CI/CD(Continuous Integration/Continuous Deployment) is a auto testing tech, most common file that triggered it is .travis.yml, which often control by a general purpose task runner, most common two file in nodejs will be Grunt file and Gulp file
    * Some js linter can also do the test, most common file such as .jshintrc, which configs the javascript linter in various way
* Documentation and Source Control
    * Git and Github are most commonly node documentation and source control application
    * Git is a underline protocol application
    * Github is a SAAS provider for the cloud based git repostory, which facilitate easy collaboration among and between teams.
    * So you will often see .git file in git repostory and .gitignore file, which implies ignore specific files from git source control
    * Additionly, since github has fantastic built-in for markdown formatting, you'll often find a README.md file in the root of the project
* Common Code-Comment
    * Not just need to write some beautiful comment, you can also use '@' to specify some vital object such as @Param for important parameter, @TODO specify a todo list, @Author for mention the author, @Date provide the log date
* Environment and Configuration
    * This is very important when it comes to local build up, 
    * Here have some most popular option when you use enviroment and configuration setting on CI/CD
    * Option 1 `NODE_ENV=<myEnvironmentName> node index.js` such as `NODE_ENV = staging or production or process node index.js` 
    * Option 2 Start you app with configuration variable you're going to need in that environment
    * Option 3 Use .ENV file, you can find a package called 'dotenv' in npm
* Styles and Patterns
    * Like the other languages, node needs a good coding styles and patterns as well, most recently style guy is [airbnb](https://github.com/airbnb/javascript)
    * Linters(jshint and jslint) also inform the syntax that many devs use
* Error Handling
    * Errback: Function should callback two parameters 1. An error(if any) 2. Data being returned(if any) if there's no error please return 'no error'
    * Avoid Throwing Exception: An uncaught exception takes down the entire thread, and kills the app. Instead, return the error or even call the errback to handle it
    * Avoid Globals: This way you'll avoid the collision with any libraries you may be using
