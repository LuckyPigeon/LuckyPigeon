import { Component, OnInit, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-main',
  templateUrl: './main.component.html',
  styleUrls: ['./main.component.scss']
})
export class MainComponent implements OnInit {
  @Output() changePage: EventEmitter<any> = new EventEmitter();
  constructor() { }

  ngOnInit() {
  }
}
