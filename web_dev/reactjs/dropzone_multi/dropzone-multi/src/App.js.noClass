import React, {useCallback} from 'react';

import {useDropzone} from 'react-dropzone'
import { useState, useEffect } from 'react';
import { Component } from 'react';
import Dropzone from 'react-dropzone'

import logo from './logo.svg';
import './App.css';

function DocumentTitleClickStateExample() {
	const [count, setCount] = useState(0);

	// Similar to componentDidMount and componentDidUpdate:
	// When you call useEffect, you're telling React to run your "effect" function after flushing changes to the DOM.
	useEffect(() => {
		// Update the document title using the browser API
		document.title = `You clicked ${count} times`;
	});

	return (
		<div>
		<p>You clicked {count} times </p>
		<button onClick={() => setCount(count + 1)}>
		Click Me
		</button>
		</div>
	);	
}

function ButtonClickStateExample() {
	// declare a new state variable, which we'll call 'count'
	const [count, setCount] = useState(0);

	return (
	  <div>
	    <p>You clicked {count} times</p>		
	    <button onClick={() => setCount(count + 1)}>
		Click me
	    </button>
	  </div>
	);
}

//function DefaultAppFunction() {
//  return (
//    <div className="App">
//      <header className="App-header">
//        <img src={logo} className="App-logo" alt="logo" />
//        <p>
//          Edit <code>src/App.js</code> and save to reload.
//        </p>
//        <a
//          className="App-link"
//          href="https://reactjs.org"
//          target="_blank"
//          rel="noopener noreferrer"
//        >
//          Learn React
//        </a>
//      </header>
//    </div>
//  );
//}

function App() {
	const onDrop = useCallback(acceptedFiles => {
		// Do something with the files
		// 
	}, [])
	const {getRootProps, getInputProps, isDragActive} = useDropZone({onDrop})

	return (
		<div {...getRootProps()}>
		  <input {...getInputProps()} />
		  {
		    isDragActive ?
			 <p>Drop the files here ..</p> :
			 <p>Drag 'n' drop some files here, or click to select files</p>
		  }
		</div>	     
	)
}

export default App;
