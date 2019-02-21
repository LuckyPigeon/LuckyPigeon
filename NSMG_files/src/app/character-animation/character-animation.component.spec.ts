import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { CharacterAnimationComponent } from './character-animation.component';

describe('CharacterAnimationComponent', () => {
  let component: CharacterAnimationComponent;
  let fixture: ComponentFixture<CharacterAnimationComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CharacterAnimationComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(CharacterAnimationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
