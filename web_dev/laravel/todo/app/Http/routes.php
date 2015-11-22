<?php

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the controller to call when that URI is requested.
|
*/

use App\Task;
use Illuminate\Http\Request;

/**
 * Display all tasks
 */
Route::get('/', function () {

	//create a view composed of all the tasks in the list
	$tasks = Task::orderBy('created_at', 'asc')->get();

	return view('tasks', [
		'tasks' => $tasks
	]);
});

/**
 * Add a new task
 */
Route::post('/task', function (Request $request) {

	//validate form input
	$validator = Validator::make($request->all(), [
	
		'name' => 'required|max:255',
	
	]);

	//if the form input is invalid display the error messages and do not submit the task
	if ($validaor->fails()) {

		return redirect('/')
			->withInput()
			->withErrors($validator);	

	}

	//if we're here, there wasn't an error so we create new task
	$task = new Task;
	$task->name = $request->name;
	$task->save();

	return redirect('/');

});

/**
 * Delete an existing task
 */
Route::delete('/task/{id}', function ($id) {

	Task::findOrFail($id)->delete();

	return redirect('/');

});

