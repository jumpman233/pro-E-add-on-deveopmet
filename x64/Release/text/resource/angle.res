! 
! 09-Apr-2001 J-01-31  Scott $$1 Created
!

(Dialog angle
                   (Components
                       (SubLayout                      Layout1)
                       (SubLayout                      Layout2)
                   )
                  (Resources
                       (.Label                         "rectangle")
                       (.DefaultButton                 "OK")
                       (.Layout
                           (Grid (Rows 1 1) (Cols 1)
                               Layout1                 Layout2
                           )
                       )
                   )
               )
              (Layout Layout1
                   (Components
                       (InputPanel                     InputPanel_1)
                       (Label                          Prompt1)
                       (InputPanel                     InputPanel_2)
                       (Label                          Prompt2)
                   )
                  (Resources
                       (InputPanel_1.Columns             4)
                       (InputPanel_1.AttachLeft          False)
                       (InputPanel_1.AttachRight         False)
                       (InputPanel_1.MinInteger          -180)
                       (InputPanel_1.MaxInteger          180)
                       (InputPanel_1.TopOffset           4)
                       (InputPanel_1.BottomOffset        4)
                       (InputPanel_1.LeftOffset          4)
                       (InputPanel_1.RightOffset         4)
					   (InputPanel_1.InputType           2)
					   (InputPanel_2.Columns             4)
                       (InputPanel_2.AttachLeft          False)
                       (InputPanel_2.AttachRight         False)
                       (InputPanel_2.MinInteger          -180)
                       (InputPanel_2.MaxInteger          180)
                       (InputPanel_2.TopOffset           8)
                       (InputPanel_2.BottomOffset        8)
                       (InputPanel_2.LeftOffset          8)
                       (InputPanel_2.RightOffset         8)
					   (InputPanel_2.InputType           2)
                       (Prompt1.Label				 "参数1")
                       (Prompt2.Label				 "参数2")
                       (.Layout
						  (Grid (Rows 2 2) (Cols 2 2)
							Prompt1  InputPanel_1  Prompt2 InputPanel_2
						  )
                       )
                   )
               )
              (Layout Layout2
                   (Components
                       (PushButton                     OK)
                       (PushButton                     Cancel)
                   )
                  (Resources
                       (OK.Label                       "OK")
                       (OK.TopOffset                   4)
                       (OK.BottomOffset                4)
                       (OK.LeftOffset                  4)
                       (OK.RightOffset                 4)
                       (Cancel.Label                   "Cancel")
                       (Cancel.TopOffset               4)
                       (Cancel.BottomOffset            4)
                       (Cancel.LeftOffset              4)
                       (Cancel.RightOffset             4)
                       (.Layout
                           (Grid (Rows 1) (Cols 1 1)
                               OK                 Cancel
                           )
                       )
                   )
               )

              